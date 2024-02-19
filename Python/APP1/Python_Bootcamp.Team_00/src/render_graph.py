import os
import json
import networkx
import nx_altair
import matplotlib.pyplot

if __name__ == '__main__':
    wiki_path = os.getenv('WIKI_FILE')

    if not wiki_path:
        print('WIKI_FILE environment variable not set')
        exit()
    try:
        graph = json.load(open(wiki_path, 'r'))
    except FileNotFoundError:
        print('Database not found')
        exit()

    graph = networkx.node_link_graph(graph)
    nodelist = list(graph.nodes())
    nodesize = [graph.degree(node) for node in nodelist]

    networkx.draw(graph, nodelist=nodelist, node_size=nodesize, with_labels=True, font_size=1, width=0.1)
    matplotlib.pyplot.savefig('graph.png', dpi=600)

    for node in graph.nodes():
        graph.nodes[node]['size'] = graph.degree(node)

    viz = nx_altair.draw_networkx(graph, node_size='size', font_size=1, width=0.1)
    viz.save('graph.html')
