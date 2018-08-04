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
#include <set>
#include <deque>
#include <queue>
using namespace std;

typedef long long ll;
ll MOD = 1000000007LL;



const int SZ = 200333;


int N, M;
ll A, B;
vector<int> children[SZ];
int cnt[SZ];
priority_queue<int> pq[SZ];
ll answer;


void init() {
	cin >> N >> M >> A >> B;
	//cout << N << endl;
	for (int v=0; v<N; v++) {
		children[v].clear();
		cnt[v] = 0;
		while (pq[v].size()) pq[v].pop();
	}
	answer = 0;

	for (int i=1; i<N; i++) {
		int parent; cin >> parent;
		children[parent].push_back(i);
	}

	for (int i=0; i<M; i++) {
		int v = (A*i + B) % N;
		cnt[v]++;
	}
}

int depth = 0;
int solve(int u) {
	depth++;
	//if (depth>1000 && depth%1000 == 0) cout << depth << endl;
	//printf("solve %d\n", u);

	if (children[u].empty()) {
		if (cnt[u] >= 1)
			answer += u;
		else 
			pq[u].push(u);
		depth--;
		return u;
	}

	vector<int> idxes;
	for (int v : children[u]) idxes.push_back(solve(v));

	int r = idxes.front();
	for (int i : idxes) 
		if (pq[r].size() < pq[i].size())
			r = i;
	pq[r].push(u);



	for (int i : idxes) if (i != r) {
		while (pq[i].size()) {
			int v = pq[i].top(); pq[i].pop();
			pq[r].push(v);
		}
	}
	for (int z=0; z<cnt[u] && int(pq[r].size())>0; z++) {
		int v = pq[r].top(); pq[r].pop();
		answer += v;
		//printf("--add %d\n", v);
	}

	depth--;
	return r;
}



int main() {
	freopen("jacks_candy_shop.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int TC; cin >> TC;
	for (int tc=1; tc<=TC; tc++) {
		init();
		solve(0);
		printf("Case #%d: %lld\n", tc, answer);
	}

	return 0;
}