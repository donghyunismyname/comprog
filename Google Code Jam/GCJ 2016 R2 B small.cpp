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


#ifdef _WIN32
#define popcnt __popcnt
#else
#define popcnt __builtin_popcount
#endif








int N, K;
double p[203];


double ans;
vector<double> cho;

void solve() {
	int limit = 1 << K;

	double candi = 0;

	for (int b = 0; b < limit; b++) if (popcnt(b) == K/2) {
		double val = 1;
		for (int i = 0; i < K; i++) {
			if ((b>>i) & 1) val *= cho[i];
			else val *= 1 - cho[i];
		}

		candi += val;
	}

	ans = max(ans, candi);
}




void go(int i, int needToChoose) {
	if (needToChoose == 0) {
		solve();
		return;
	}
	if (i == N) return;
	if (needToChoose > N - i) return;

	go(i + 1, needToChoose);
	cho.push_back(p[i]);
	go(i + 1, needToChoose - 1);
	cho.pop_back();
}



int main() {

	//freopen("input.txt", "r", stdin);
	freopen("B-small-attempt1.in", "r", stdin);
	freopen("output.txt", "w", stdout);



	int TC; cin >> TC;
	for (int tc = 1; tc <= TC; tc++) {
		printf("Case #%d: ", tc);

		cin >> N >> K;
		FOR(i, N) cin >> p[i];
		
		ans = -123;
		go(0, K);

		printf("%.10lf\n", ans);
	}


	return 0;
}
