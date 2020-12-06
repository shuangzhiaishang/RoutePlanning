#include "graph.h"

#include<iostream>
#include<queue>

#include "pugixml.hpp"

Graph::Graph() {
	nodes.clear();
	mp.clear();
}

// compute distance between Nodes
double distance(Node& n1, Node& n2) {
	return 1.0;
}

void Graph::LoadNode() {
	pugi::xml_document xdoc;
	if (!xdoc.load_file(FileName)) {
		return;
	}

	pugi::xml_node xosm = xdoc.child("osm");
	int idx = 0;
	for (pugi::xml_node xnode = xosm.child("node"); xnode != NULL; xnode = xnode.next_sibling("node")) {
		long long id = xnode.attribute("id").as_llong();

		double lon = xnode.attribute("lon").as_double();

		double lat = xnode.attribute("lat").as_double();

		nodes.push_back(Node(id, lon, lat));
		mp[id] = idx++;
	}

	std::cout << "nodes numbers:" << nodes.size() << std::endl;
}

void Graph::LoadEdge() {
	pugi::xml_document xdoc;
	if (!xdoc.load_file(FileName)) {
		return;
	}

	pugi::xml_node xosm = xdoc.child("osm");
	int num_edges = 0;
	for (pugi::xml_node xway = xosm.child("way"); xway; xway = xway.next_sibling("way")) {
		pugi::xml_node xnode1 = xway.child("nd");
		pugi::xml_node xnode2 = xnode1.next_sibling("nd");

		while (xnode2) {
			num_edges++;

			// search nodes
			int idx1 = mp[xnode1.attribute("ref").as_llong()], idx2 = mp[xnode2.attribute("ref").as_llong()];

			// add edge
			nodes[idx1].edges.push_back(Edge(idx2, distance(nodes[idx1], nodes[idx2])));

			// next edge
			xnode1 = xnode2;
			xnode2 = xnode2.next_sibling("nd");
		}
	}
	std::cout << "edge nums:" << num_edges << std::endl;
}

void ShortestPath() {

}

void Graph::print() const {
	for (const Node& node : nodes) {
		node.print();
		std::cout << "Edges:\n";
		for (const Edge& edge : node.edges) {
			std::cout << node.id << " -> " << nodes[edge.vertex].id << std::endl;
		}
	}
}

void Graph::BFS(int idx) {
	int visit[2000];
	memset(visit, 0, sizeof(visit));
	visit[idx] = 1;
	std::queue<int>q;
	q.push(idx);
	int cnt = 0;
	while (!q.empty()) {
		int i = q.front();
		q.pop();

		Node n = nodes[i];
		for (const Edge& edge : n.edges) {
			if (!visit[edge.vertex]) {
				cnt++;
				std::cout << nodes[edge.vertex].id << std::endl;
				visit[edge.vertex] = 1;
				q.push(edge.vertex);
			}
		}
	}
	std::cout << "reachable nodes:" << cnt << std::endl;
}