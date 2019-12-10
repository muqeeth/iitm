#include "graphreader.h"
#include<string.h>
#include<limits.h>
#include<iostream>
#include<vector>
#include<list>
#include<queue>

using namespace std;

typedef struct FlowEdge{
	int a,b,flow,edge_id;
}FlowEdge;

vector < FlowEdge > flows;

void PrintFlow(vector < FlowEdge > f)
{
	for(int i = 0; i < f.size(); i++)
		cout << f[i].a << " " << f[i].b << " " << f[i].flow << endl;
	cout << endl;
}

bool BFS(Graph G, int s, int t, int * level)
{
	for(int i = 0; i < G.no_nodes; i++)
		level[i] = -1;

	level[s] = 0;

	list < int > q;
	q.push_back(s);

	while(!q.empty())
	{
		int u = q.front();
		q.pop_front();

		for(int i = 0; i != G.nodes[u].adj.size(); i++)
		{
			if((level[G.nodes[u].adj[i]->id] < 0) && (G.nodes[u].adj[i]->flow < G.nodes[u].adj[i]->C))
			{
				level[G.nodes[u].adj[i]->id] = level[u] + 1;
				q.push_back(G.nodes[u].adj[i]->id);
			}
		}
	}

	return level[t] < 0 ? false : true ;
}

int SendFlow(Graph G, int u, int flow, int t, int start[],int * level)
{
	if(u == t)
		return flow;

	for(;start[u] < G.nodes[u].adj.size();start[u]++)
	{
		adj_node * e = G.nodes[u].adj[start[u]];
		if((level[e->id] == level[u]+1) && ((e->flow) < (e->C)))
		{
			int current_flow = min(flow, (e->C)-(e->flow));
			int temp_flow = SendFlow(G,e->id,current_flow,t,start,level);

			if(temp_flow > 0)
			{
				G.nodes[u].adj[start[u]]->flow += temp_flow;
				FlowEdge f;
				f.a = u;
				f.b = G.nodes[u].adj[start[u]]->id;
				f.flow = temp_flow;
				f.edge_id = G.nodes[u].adj[start[u]]->edge_id;
				flows.push_back(f);

				for(int i = 0; i < G.nodes[e->id].adj.size(); i++)
				{
					if(u == G.nodes[e->id].adj[i]->id)
					{
						G.nodes[e->id].adj[i]->flow -= temp_flow;
						break;
					}
				}

				return temp_flow;
			}
		}
	}

	return 0;
}

int DinicMaxFlow(Graph G, int s, int t, int * level)
{
	if(s == t)
		return -1;

	int total_flow = 0;

	while(BFS(G,s,t,level) == true)
	{	
		int * start = new int[G.no_nodes+1];
		while(int flow = SendFlow(G,s,INT_MAX,t,start,level))
			total_flow += flow;
	}

	return total_flow;
}

int main()
{
	Graph G;
	G.read_graph("tn_graph.txt");
	int * level = new int[G.no_nodes];
	

	for(int i = 0; i < G.no_edges ; i++)
	{
		int a = G.edges[i].nodes[0];
		int b = G.edges[i].nodes[1];
		adj_node * temp_a = new adj_node;
		adj_node * temp_b = new adj_node;

		temp_a->id = a;
		temp_b->id = b;
		temp_a->dist = temp_b->dist = G.edges[i].distance;
		temp_a->edge_id = temp_b->edge_id = i;

		if(G.edges[i].type == 'p')
			temp_a->C = temp_b->C = 100;
		else if(G.edges[i].type == 's')
			temp_a->C = temp_b->C = 50;
		else if(G.edges[i].type == 't')
			temp_a->C = temp_b->C = 20;

		temp_a->flow = temp_b->flow = 0;
		temp_a->rev = b;
		temp_b->rev = a;

		G.nodes[a].adj.push_back(temp_b);
		G.nodes[b].adj.push_back(temp_a);
	}

	// cout << G.no_nodes << endl;
	G.Print_nodes();

	// cout << G.no_edges << endl;
	G.Print_edges();

	int source,destination;
	cin >> source >> destination;
	cout << source << " " << destination<< endl;
	int max_flow = DinicMaxFlow(G,source,destination,level);
	vector < int > edge_flows(G.no_edges);
	// cout<<"Printing now"<<endl;
	for(int i = 0; i < flows.size(); i++)
	{
		edge_flows[flows[i].edge_id] += flows[i].flow;
		G.edges[flows[i].edge_id].nodes[0] = flows[i].a;
		G.edges[flows[i].edge_id].nodes[1] = flows[i].b;
	}

	for(int i = 0; i < G.no_edges; i++)
	{
		if(edge_flows[i] > 0)
		{
			cout << G.edges[i].nodes[0] << " " << G.edges[i].nodes[1] << " " << edge_flows[i] << endl;
		}
	}

	cout << "Maximum flow " << max_flow << endl;
	
	

	return 0;
}