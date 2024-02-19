import os
import json
import argparse
import urllib.parse


class Pathfinder:
    def __init__(self, from_page, to_page, non_directed):
        self.from_page = '/wiki/' + urllib.parse.quote(from_page.replace(' ', '_'))
        self.to_page = '/wiki/' + urllib.parse.quote(to_page.replace(' ', '_'))
        self.non_directed = non_directed
        wiki_path = os.getenv('WIKI_FILE')

        if not wiki_path:
            print('WIKI_FILE environment variable not set')
            exit()
        try:
            self.graph = json.load(open(wiki_path, 'r'))
        except FileNotFoundError:
            print('Database not found')
            exit()

        ids = [node['id'] for node in self.graph['nodes']]

        if self.from_page not in ids or self.to_page not in ids:
            print('From page or To page not in graph')
            exit()
        if self.non_directed:
            self.make_non_directed()

    def make_non_directed(self):
        reversed_links = []

        for edge in self.graph['links']:
            reverse_edge = {
                'source': edge['target'],
                'target': edge['source']
            }

            reversed_links.append(reverse_edge)

        self.graph['links'] += reversed_links

    def find_path(self):
        if self.from_page == self.to_page:
            return 0

        queue = [(self.from_page, 0, [self.from_page])]
        added = set([self.from_page])
        pathes = []

        while queue:
            node = queue.pop(0)

            for edge in self.graph['links']:
                if edge['source'] == node[0] and edge['target'] == self.to_page:
                    pathes.append((node[1] + 1, node[2] + [edge['target']]))
                elif edge['source'] == node[0] and edge['target'] not in added:
                    queue.append((edge['target'], node[1] + 1, node[2] + [edge['target']]))
                    added.add(edge['target'])

        return min(pathes) if pathes else None


if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument('--from', dest='from_page', help='start page', required=True)
    parser.add_argument('--to', dest='to_page', help='finish page', required=True)
    parser.add_argument('--non-directed', dest='non_directed', help='non directed graph', action='store_true',
                        required=False)
    parser.add_argument('-v', dest='verbose', help='show path', action='store_true', required=False)

    args = parser.parse_args()
    pathfinder = Pathfinder(args.from_page, args.to_page, args.non_directed)
    result = pathfinder.find_path()

    if result:
        if args.verbose:
            print(' -> '.join(result[1]))

        print(result[0])
    else:
        print('No path found')
