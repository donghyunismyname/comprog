#define _CRT_SECURE_NO_WARNINGS // scanf(), gets() (needed for Visual C++)

#include <cassert>

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>

using namespace std;

#define MEMSET(x, WITH) memset(x, (WITH), sizeof(x))
#define FOR(i, E) for (int i=0; i<(E); i++)

typedef long long ll;
const ll MOD = 1000000007;
const double PI = atan(1) * 4;



struct UnionFind {
	vector<int> parent;

	UnionFind(int size) : parent(size, -1) {}

	int find(int a) {
		if (parent[a] < 0) return a;
		return parent[a] = find(parent[a]);
	}

	// Returns false if a and b are already contained it the same set
	bool merge(int a, int b) {
		a = find(a); b = find(b);
		if (a == b) return false;

		// a should be the parent of b
		if (parent[a] > parent[b]) swap(a, b);
		parent[a] += parent[b];
		parent[b] = a;

		return true;
	}

	void clear() {
		for (int &p : parent) p = -1;
	}
};





int N;
char know[33][33];

int cnt1[103];
int cnt2[103];
int already[103];



int main() {
	freopen("D-small-practice.in", "r", stdin);
	freopen("output.txt", "w", stdout);



	int TC; cin >> TC;
	for (int tc = 1; tc <= TC; tc++) {
		printf("Case #%d: ", tc);

		cin >> N;
		FOR(i, N) cin >> know[i];

		bool all0 = true;
		FOR(i, N) FOR(j, N) all0 = all0 && know[i][j] == '0';
		if (all0) {
			cout << N << endl;
			continue;
		}


		
		UnionFind uf(2*N);
		FOR(i, N) FOR(j, N) if (know[i][j] == '1')
			uf.merge(i, N + j);
			


		MEMSET(cnt1, 0);
		MEMSET(cnt2, 0);
		MEMSET(already, 0);

		FOR(i, N) cnt1[uf.find(i)]++;
		FOR(j, N) cnt2[uf.find(N + j)]++;
		FOR(i, N) FOR(j, N) if (know[i][j] == '1')
			already[uf.find(i)]++;


		int ans = 0;
		vector<pair<int, int>> rec;
		int rec10 = 0;
		int rec01 = 0;
		
		FOR(t, 2 * N) if (t == uf.find(t)) {
			ans += cnt1[t] * cnt2[t] - already[t];
			//cout << already[t] << endl;

			if (cnt1[t] != cnt2[t]) {
				if (cnt1[t] == 0) rec01++;
				else if (cnt2[t] == 0) rec10++; 
				else
					rec.push_back({ cnt1[t], cnt2[t] });
			}
		}
		//printf("[ds] %d %d     ", rec10, rec01);
		int minval = min(rec10, rec01);
		ans += minval;
		rec10 -= minval;
		rec01 -= minval;

		while (rec10--) rec.push_back({ 1, 0 });
		while (rec01--) rec.push_back({ 0, 1 });



		assert(rec.size() != 1);
		if (rec.size() >= 2) {
			//printf("[rec[0]] %d %d\n", rec[0].first, rec[0].second);
			//printf("[rec[1]] %d %d\n", rec[1].first, rec[1].second);

			int toAdd = (rec[0].first + rec[1].first) * (rec[0].second + rec[1].second)
				- rec[0].first * rec[0].second
				- rec[1].first * rec[1].second;
			//printf("[toAdd] %d\n", toAdd);
			ans += toAdd;
		}




		cout << ans << endl;

	}


	return 0;
}
