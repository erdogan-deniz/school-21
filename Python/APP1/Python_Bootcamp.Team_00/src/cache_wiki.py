import argparse
import logging
import urllib.parse
import requests
from bs4 import BeautifulSoup
import json
import networkx
import neonx

logging.basicConfig(level=logging.INFO)

class WikiCacher:
	def __init__(self, start_page, depth_limit):
		self.domain = 'https://en.wikipedia.org'
		self.start_page = urllib.parse.quote(start_page.replace(' ', '_'))
		self.depth_limit = depth_limit
		self.pages_limit = 1000
		self.pages = set()
		self.edges = []

	def get_links(self, a_tags):
		for a_tag in a_tags:
			link = str(a_tag['href'])
			if link.startswith('/wiki/') and ':' not in link:
				yield link

	def visit(self, visiting_page, depth):
		if len(self.pages) > self.pages_limit or depth > self.depth_limit:
			return
		current_page = visiting_page.removeprefix(self.domain)
		logging.info(current_page)
		self.pages.add(current_page)
		html = requests.get(visiting_page)
		soup = BeautifulSoup(html.text, 'html.parser')
		content = soup.find('div', {'id': 'mw-content-text'})
		a_tags = content.find_all('a', href=True)
		for link in self.get_links(a_tags):
			if (current_page, link) not in self.edges and (link, current_page) not in self.edges:
				self.edges.append((current_page, link))
			if link not in self.pages:
				self.visit(self.domain + link, depth + 1)

	def cache(self):
		self.visit(self.domain + '/wiki/' + self.start_page, 0)

	def save_json(self):
		graph = networkx.Graph()
		graph.add_edges_from(self.edges)
		json.dump(networkx.node_link_data(graph), open('graph.json', 'w'))
	
	def import_to_neo4j(self):
		graph = networkx.Graph()
		graph.add_edges_from(self.edges)
		neonx.write_to_neo("http://localhost:7474/db/data/", graph, 'LINK')	

if __name__ == '__main__':
	parser = argparse.ArgumentParser()
	parser.add_argument('-p', dest='start_page', help='start page', required=True)
	parser.add_argument('-d', dest='depth_limit', help='depth limit', type=int, default=3)
	args = parser.parse_args()
	cacher = WikiCacher(args.start_page, args.depth_limit)
	cacher.cache()
	cacher.save_json()
