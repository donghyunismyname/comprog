#define _CRT_SECURE_NO_WARNINGS
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
using namespace std;
#include <set>

typedef long long ll;
ll MOD = 1000000007LL;

int N, M;
set<int> adj[200333];
//bool alive[200333];

int main() {
	setbuf(stdout, 0);
	int TC; scanf("%d", &TC);
	for (int tc=1; tc<=TC; tc++) {
		scanf("%d%d", &N, &M);
		for (int v=1; v<=N; v++) adj[v].clear();
		for (int z=0; z<M; z++) {
			int u, v; scanf("%d%d", &u, &v);
			adj[u].insert(v);
			adj[v].insert(u);
		}


		//memset(alive, 0, sizeof(alive));
		//for (int v=1; v<=N; v++) alive[v] = true;

		int ans = N;
		for (int i=1; i<=N; i++) {
			vector<int> st;
			st.push_back(i);
			while (st.size()) {
				int x = st.back(); st.pop_back();
				if (adj[x].size() != 2) continue;

				int u = *adj[x].begin();
				int v = *next(adj[x].begin());
				if (adj[u].find(v) == adj[u].end()) continue;

				ans--;

				adj[x].erase(u);
				adj[x].erase(v);
				adj[u].erase(x);
				adj[v].erase(x);

				st.push_back(u);
				st.push_back(v);
			}
		}

		

		printf("Case #%d\n", tc);
		printf("%d\n", ans);
	}

	return 0;
}