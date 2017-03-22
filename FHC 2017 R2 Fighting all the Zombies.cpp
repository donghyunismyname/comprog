/*
https://www.facebook.com/hackercup/problem/1726375930948061/
Facebook Hacker Cup 2017 Round 2
Fighting all the Zombies

2017-03-22
*/

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

#define MEMSET(x, WITH) memset(x, (WITH), sizeof(x))
#define FOR(i, E) for (int i=0; i<(E); i++)
typedef long long ll;
const ll MOD = 1000000007;
//const double PI = atan(1) * 4;






struct Info {
	ll x[2][2];
	Info operator*(const Info &b) {
		Info ret;
		FOR(i, 2) FOR(j, 2)
			ret.x[i][j] = x[i][0] * b.x[0][j] + x[i][1] * b.x[1][j],
			ret.x[i][j] %= MOD;
		return ret;
	}

	void init() {
		x[0][0] = 1;
		x[0][1] = 0;
		x[1][0] = 1;
		x[1][1] = 0;
	}
};

struct SegTree {
	static const int SZ = 1 << 21;
	static const int base = SZ / 2;
	Info tr[SZ];

	void init() {
		for (int i = 0; i < SZ; i++) tr[i].init();
	}

	void update(int idx, ll a, ll d) {
		idx += base;
		tr[idx].x[0][0] = a;
		tr[idx].x[0][1] = d;

		for (idx /= 2; idx; idx /= 2)
			tr[idx] = tr[idx * 2] * tr[idx * 2 + 1];
	}

	ll getAns() {
		return tr[1].x[0][0];
	}
} seg;




int N, M;
ll W, Aw, Bw;
ll D, Ad, Bd;
ll S, As, Bs;

ll aAcc[800333];
ll dAcc[800333][2];

int main() {
	freopen("fighting_all_the_zombies.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int TC; scanf("%d", &TC);
	for (int tc = 1; tc <= TC; tc++) {
		scanf("%d%d", &N, &M);
		scanf("%lld%lld%lld", &W, &Aw, &Bw);
		scanf("%lld%lld%lld", &D, &Ad, &Bd);
		scanf("%lld%lld%lld", &S, &As, &Bs);


		seg.init();
		fill(aAcc + 1, aAcc + 1 + N, 1LL);
		MEMSET(dAcc, 0);
		ll ans = 0;


		{
			ll Z = max((ll)1, min((ll)N, W + D - 1));
			int idx = (W + Z) / 2;
			if (W == Z)
				aAcc[idx] = (aAcc[idx] + S) % MOD;
			else
				dAcc[idx][W & 1] = (dAcc[idx][W & 1] + S) % MOD;

			seg.update(idx, aAcc[idx], dAcc[idx][0] * dAcc[idx][1] % MOD);
			ans = (ans + seg.getAns()) % MOD;
		}


		for (int zz = 2; zz <= M; zz++) {
			W = (Aw*W + Bw) % N + 1;
			D = (Ad*D + Bd) % 3;
			S = (As*S + Bs) % 1000000000 + 1;

			ll Z = max((ll)1, min((ll)N, W + D - 1));
			int idx = (W + Z) / 2;
			if (W == Z)
				aAcc[idx] = (aAcc[idx] + S) % MOD;
			else
				dAcc[idx][W & 1] = (dAcc[idx][W & 1] + S) % MOD;

			seg.update(idx, aAcc[idx], dAcc[idx][0] * dAcc[idx][1] % MOD);
			ans = (ans + seg.getAns()) % MOD;
		}




		printf("Case #%d: %lld\n", tc, ans);
	}

	return 0;
}