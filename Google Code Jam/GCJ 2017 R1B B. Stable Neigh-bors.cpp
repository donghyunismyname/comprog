/*
Google Code Jam 2017
Round 1B
Problem B. Stable Neigh-bors
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


const char* imp = "IMPOSSIBLE";
int N, R, O, Y, G, B, V;

struct Color {
	int cnt;
	char ch;
	int cnt2;
	char ch2;
	bool operator<(Color rhs) {
		return cnt < rhs.cnt;
	}
	void put() {
		putchar(ch); cnt--;
		while (cnt2) {
			putchar(ch2); cnt2--;
			putchar(ch);
		}
	}
};


int main() {
	freopen("B-large-practice.in", "r", stdin);
	freopen("output.txt", "w", stdout);

	int TC; scanf("%d", &TC);
	for (int tc = 1; tc <= TC; tc++) {
		printf("Case #%d: ", tc);
		scanf("%d %d %d %d %d %d %d", &N, &R, &O, &Y, &G, &B, &V);

		Color arr[3] = {
			{R, 'R', G, 'G'},
			{Y, 'Y', V, 'V'},
			{B, 'B', O, 'O'},
		};
		FOR(i, 3) {
			Color &z = arr[i];
			if (z.cnt2 == 0) continue;
			else if (z.cnt < z.cnt2) goto IMP;
			else if (z.cnt == z.cnt2 && z.cnt + z.cnt2 != N) goto IMP;
			else if (z.cnt == z.cnt2) {
				while (z.cnt--) {
					putchar(z.ch);
					putchar(z.ch2);
				}
				puts("");
				goto EXIT;
			}
			else z.cnt -= z.cnt2;
		}


		sort(arr, arr + 3);
		Color a = arr[2];
		Color b = arr[1];
		Color c = arr[0];
		if (a.cnt > b.cnt + c.cnt) goto IMP;

		while (a.cnt != b.cnt + c.cnt) {
			a.put();
			b.put();
			c.put();
		}
		while (b.cnt) {
			a.put();
			b.put();
		}
		while (c.cnt) {
			a.put();
			c.put();
		}
		puts("");
		goto EXIT;
		

	IMP:
		puts("IMPOSSIBLE");
	EXIT:;
	}


	return 0;
}
