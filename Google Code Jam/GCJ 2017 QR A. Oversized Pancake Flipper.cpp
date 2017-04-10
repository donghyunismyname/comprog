/*
Google Code Jam 2017
Qualification Round
A. Oversized Pancake Flipper
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
//const ll MOD = 1000000007;
//const double PI = atan(1) * 4;


char flip(char c) {
	if (c == '+') return '-';
	else if (c == '-') return '+';
	else assert(false);
}

char S[1003];
int K;


int main() {
	freopen("A-large.in", "r", stdin);
	freopen("output.txt", "w", stdout);

	int TC; scanf("%d", &TC);
	for (int tc = 1; tc <= TC; tc++) {
		printf("Case #%d: ", tc);

		scanf("%s %d", S, &K);

		int ans = 0;
		int i = 0;
		for (; S[i+K-1]; i++) if (S[i] == '-') {
			ans++;
			for (int ii=i; ii<i+K; ii++)
				S[ii] = flip(S[ii]);
		}



		bool possible = true;
		for (int ii=i; S[ii]; ii++) if (S[ii] == '-') {
			possible = false;
			break;
		}
		if (!possible) {
			puts("IMPOSSIBLE");
			continue;
		}
		


		printf("%d\n", ans);
	}


	return 0;
}
