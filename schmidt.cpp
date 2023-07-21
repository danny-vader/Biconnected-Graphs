#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <unistd.h>
#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

ll depth_first_count = 0;

vector <string> &split(const string &s, char delim, vector <string> &elems) {
	stringstream ss(s);
	string item;
	
	while (getline(ss, item, delim))
		elems.push_back(item);
	
	return elems;
}

vector <string> split(const string &s, char delim) {
	vector <string> elems;
	split(s, delim, elems);
	
	return elems;
}

void dfs(vector <vector<ll>> &adj, vector<bool> &dfs_visited, vector <ll> &dfs_queue, vector <ll> &dfs_parent, ll u) {
	dfs_visited[u] = true;
	dfs_queue.push_back(u);
	
	for (auto v: adj[u]) {
		if (!dfs_visited[v]) {
			dfs_parent[v] = u;
			dfs(adj, dfs_visited, dfs_queue, dfs_parent, v);
		}
	}
}

int cycle_chain_count = 0;

void
ear_decomposition(vector<bool> &ear_visited, vector <ll> &dfs_queue, vector <ll> dfs_parent, vector <vector<ll>> &adj) {
	for (auto u: dfs_queue) {
		for (auto v: adj[u]) {
			if (dfs_parent[u] == v || dfs_parent[v] == u) {
				continue;
			}
			
			ear_visited[u] = true;
			bool is_cycle = false;
			
			for (ll x = v;; x = dfs_parent[x]) {
				if (x == u) is_cycle = true;
				
				if (ear_visited[x]) break;
				ear_visited[x] = true;
			}
			
			cycle_chain_count += is_cycle;
		}
	}
}

bool check_nodes_visited(vector<bool> &v) {
	for (auto it: v) {
		if (it == false) {
			return false;
		}
	}
	
	return true;
}

int main(int argc, char *argv[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int k;
	int n, m;
	char fname[100], graph_type[250];
	string line, pname;
	vector <string> nbrs;
	vector <vector<ll>> adj;
	
	if (argc != 2) {
		printf("\nInappropriate arguments! \n\nExpected <graph_name> as input!!\n");
		return 1;
	}
	
	strcpy(fname, argv[1]);
	ifstream fin(fname);
	
	nbrs = split(string(fname), '/');
	pname = nbrs[nbrs.size() - 1];
	
	k = 0;
	bool take_edges_now = false;
	
	while (getline(fin, line)) {
		if (!k) {
			strcpy(graph_type, line.c_str());
			k = 1;
		}
		
		if (line[0] == '%')
			continue;
		
		nbrs = split(line, ' ');
		int a = atoi(nbrs[0].c_str()), b = atoi(nbrs.back().c_str());
		if (!take_edges_now) {
			n = a, m = b;
			take_edges_now = true;
			adj.resize(n);
		} else {
			if (nbrs.size() == 3) b = atoi(nbrs[1].c_str());
			
			a--;
			b--;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
	}
	
//	printf("\n\nGraph : %s \nNodes: %d \nEdges: %d \nType: %s\n\n", pname.c_str(), n, m, graph_type + 2);
	
	ll dfs_root = 0;
	vector<bool> dfs_visited(n, false);
	vector <ll> dfs_queue;
	vector <ll> dfs_parent(n, -1);
	dfs(adj, dfs_visited, dfs_queue, dfs_parent, dfs_root);
	
	if (!check_nodes_visited(dfs_visited)) {
		cout << "NO" << endl;
		return 0;
	}
	
	vector <vector<ll>> ears;
	vector<bool> ear_visited(n, false);
	
	ear_decomposition(ear_visited, dfs_queue, dfs_parent, adj);
	
	
	if (check_nodes_visited(ear_visited) && cycle_chain_count == 1) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
}
