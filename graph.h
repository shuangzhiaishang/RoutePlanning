/**
 * Store graph with adjacency list
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include<iostream>
#include<vector>
#include<unordered_map>

const char* const FileName = "map.osm";

struct Edge {
	int vertex;      // subscript in nodes
	int weight;      // distance between nodes

	explicit Edge(long long id = 0, int weight_ = 0) :
		vertex(id),
		weight(weight_) {
	}
};

struct Node {
	long long id;              // osm node id
	double lon, lat;           // longtitude, latitude
	std::vector<Edge> edges;   // connected edges

	explicit Node(long long id_ = 0, double lon_ = 0.0, double lat_ = 0.0) {
		id = id_;
		lon = lon_;
		lat = lat_;
		edges.clear();
	}

	void print() const {
		std::cout << "Id:" << id << ",lontitude:" << lon << ",latitude:" << lat << std::endl;
	}
};

class Graph {
private:
	std::vector<Node>nodes;
	std::unordered_map<long long, int> mp;  // where node is stored in nodes    node.id  ->  i (nodes[i] = node)

public:
	Graph();
	void LoadNode();
	void LoadEdge();
	void ShortestPath();
	void BFS(int idx);
	void print() const;
};

// compute distance between nodes
double distance(Node& n1, Node& n2);

#endif // !GRAPH_H_
