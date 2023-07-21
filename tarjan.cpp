#include "bits/stdc++.h"
using namespace std;
#define for_(i, s, e) for (int i = s; i < (int) e; i++)
typedef long long ll;
typedef vector<int> vi;

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
	
	vector<bool> vis(n);
	vi tin(n, -1), low(n, -1);
	int tim = 0;
	bool biconn = true;
	
	function<void(int, int)> dfs = [&](int v, int p) {
		if (!biconn) return;
		
		vis[v] = true;
		tin[v] = low[v] = tim++;
		
		int children = 0;
		
		for (auto i: adj[v]) {
			if (!biconn) return;
			
			if (i != p) {
				if (vis[i]) {
					low[v] = min(low[v], tin[i]);
					continue;
				}
				
				dfs(i, v);
				
				if (!biconn) return;
				
				low[v] = min(low[v], low[i]);
				
				if (low[i] >= tin[v] and p != -1) {
					biconn = false;
					return;
				}
				
				children++;
			}
		}
		
		// root should have a single child
		if (p == -1 && children > 1) biconn = false;
	};
	
	dfs(0, -1);
	
	for_(i, 0, n) if (!vis[i]) {
		biconn = false;
		break;
	}
	
	cout << (biconn ? "YES" : "NO") << endl;
}


