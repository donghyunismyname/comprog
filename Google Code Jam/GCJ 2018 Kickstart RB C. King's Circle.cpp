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

typedef long long ll;
ll MOD = 1000000007LL;



// The index starts from 1
// tree[0] is never used
struct Fenwick {
	static const int ARRAYSIZE = 1000333;
	ll tree[ARRAYSIZE];

	ll sumTo(int hi) {
		ll ret = 0;
		for (; hi; hi -= hi&-hi)
			ret += tree[hi];
		return ret;
	}

	void add(int idx, int val) { // Enters infinit loop on argument idx = 0
		for (; idx<ARRAYSIZE; idx += idx&-idx)
			tree[idx] += val;
	}

	ll psum(int lo, int hi) {
		return -sumTo(lo - 1) + sumTo(hi);
	}

	ll sumFrom(int lo) {
		return psum(lo, ARRAYSIZE - 1);
	}

	void clear() {
		memset(tree, 0, sizeof(tree));
	}
};
Fenwick fen;
Fenwick acc;



ll N;
ll V, H;
ll A, B, C, D, E, F;
ll M;


int main() {
	freopen("C-large-practice.in", "r", stdin);
	freopen("output.txt", "w", stdout);

	int TC; cin >> TC;
	for (int tc=1; tc<=TC; tc++) {
		cin >> N;
		cin >> V >> H;
		cin >> A >> B >> C >> D >> E >> F;
		cin >> M;

		vector<pair<int, int>> pts;
		for (int i=1; i<=N; i++) {
			pts.push_back(make_pair(V+1, H+1));

			ll VV = (A*V + B*H + C) % M;
			ll HH = (D*V + E*H + F) % M;
			V = VV;
			H = HH;
		}


		ll ans = 0;
		sort(pts.begin(), pts.end());

		for (int z=0; z<2; z++) {
			fen.clear();
			acc.clear();
			reverse(pts.begin(), pts.end());

			vector<pair<int, int>> addfen, addacc;
			for (int i=0; i<pts.size(); i++) {
				if (i>=1 && pts[i-1].first != pts[i].first) {
					for (auto x: addfen) fen.add(x.first, x.second);
					for (auto x: addacc) acc.add(x.first, x.second);
					addfen.clear();
					addacc.clear();
				}

				auto p = pts[i];
				ll S = fen.sumTo(p.second-1);
				ans += acc.sumTo(p.second-1);
				addfen.push_back(make_pair(p.second, 1));
				addacc.push_back(make_pair(p.second, S));
			}
		}



		ans = N*(N-1)*(N-2)/6 - ans;
		printf("Case #%d: %lld\n", tc, ans);
	}

	return 0;
}