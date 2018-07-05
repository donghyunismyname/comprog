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






ll N, M, L;

struct Point {
	ll x, y;
	ll left() {
		return x - y;
	}
	ll right() {
		return x + y;
	}
};
Point pts[200333];


bool possible(ll H) {
	vector<Point> p;
	for (int i=0; i<=M; i++) {
		if (pts[i].y <= H)
			p.push_back(pts[i]);

		if (i < M) if (pts[i].y > H && H > pts[i+1].y || pts[i].y < H && H < pts[i+1].y) {
			int diff = abs(pts[i].y - H);
			p.push_back({ pts[i].x+diff, H });
		}
	}


	int cnt = 0;
	ll x = 0;
	for (int i=0; x<N; ) {
		if (i == p.size()) return false;
		if (x < p[i].left()) return false;
		while (i+1 < p.size() && p[i+1].left() <= x) i++;

		cnt++; if (L < cnt) return false;
		x = p[i].right();
		i++;
	}

	return true;
}


int main() {
	setbuf(stdout, 0);
	int TC; scanf("%d", &TC);
	for (int tc=1; tc<=TC; tc++) {
		scanf("%lld%lld%lld", &N, &M, &L);

		for (int i=0; i<=M; i++) {
			ll x, y; scanf("%lld%lld", &x, &y);
			pts[i].x = x*2;
			pts[i].y = y*2;
		}
		N *= 2;

		
		ll hi = 1000000000000 * 2;
		if (!possible(hi)) {
			printf("Case #%d\n", tc);
			printf("-1\n");
			continue;
		}

		ll lo = 0;
		while (lo+2<=hi) {
			ll mi = (lo + hi)/2;
			if (possible(mi))
				hi = mi;
			else
				lo = mi;
		}

		printf("Case #%d\n", tc);
		if (hi%2 == 0)
			printf("%lld 1\n", hi/2);
		else
			printf("%lld 2\n", hi);
	}

	return 0;
}

