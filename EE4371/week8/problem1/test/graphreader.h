#include<stdlib.h>
#include<fstream>
#include<iostream>
#include<vector>

using namespace std;

typedef struct adj_node{
	int id,flow,C,rev,edge_id;
	double dist;
}adj_node;

typedef struct Node{
	double lattitude,longitude;
	vector < adj_node *>adj;
}Node;

typedef struct Edge{
	char type;
	unsigned long nodes[2];
	double distance;
}Edge;

typedef struct Graph{
	Edge * edges;
	Node * nodes;
	unsigned long no_nodes, no_edges;

	int * level;
	vector < Edge > * adj;

	bool read_graph(const char * file_name)
	{
		ifstream file;
		file.open(file_name);
		if(file)
			file >> no_nodes;
		else
		{
			cout << "[!] Nodes input file is empty." << endl;
			exit(0);
		}
		
		nodes = (Node *)malloc(sizeof(Node)*no_nodes);
		for(unsigned i = 0; i < no_nodes; i++)
		{
			file >> nodes[i].lattitude;
			file >> nodes[i].longitude;
		}

		file >> no_edges;
		edges = (Edge *)malloc(sizeof(Edge)*no_edges);
		for(unsigned i = 0; i < no_edges; i++)
		{
			file >> edges[i].nodes[0];
			file >> edges[i].nodes[1];
			file >> edges[i].type;
			file >> edges[i].distance;
		}

		file.close();
	}

	void Print_nodes()
	{
		for(int i = 0; i < no_nodes; i++)
		{
			cout << i << " " << nodes[i].lattitude << " " << nodes[i].longitude << " " << endl;
		}
	}

	void Print_edges()
	{
		for(int i = 0; i < no_edges; i++)
		{
			cout << edges[i].nodes[0] << " " << edges[i].nodes[1] << " " <<edges[i].type << " " << edges[i].distance << endl;
		}
	}

	void Clearer()
	{
		free(this->nodes);
		free(this->edges);
	}
}Graph;