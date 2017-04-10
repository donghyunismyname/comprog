/*
Google Code Jam 2017
Qualification Round
C. Bathroom Stalls
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


void printAns(ll val) {
	printf("%lld %lld\n", val/2, (val-1)/2);
}


int main() {
	freopen("C-large.in", "r", stdin);
	freopen("output.txt", "w", stdout);

	int TC; scanf("%d", &TC);
	for (int tc = 1; tc <= TC; tc++) {
		ll N, K; scanf("%lld %lld", &N, &K);


		ll B = 1;
		while (2*B <= K) B *= 2;

		ll q = (N - B + 1) / B;
		ll r = (N - B + 1) % B;

		printf("Case #%d: ", tc);
		
		if (K <= B + r - 1)
			printAns(q+1);
		else
			printAns(q);
	}


	return 0;
}
