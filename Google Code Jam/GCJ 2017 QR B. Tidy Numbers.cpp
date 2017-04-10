/*
Google Code Jam 2017
Qualification Round
B. Tidy Numbers
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




int main() {
	freopen("B-large.in", "r", stdin);
	freopen("output.txt", "w", stdout);

	int TC; scanf("%d", &TC);
	for (int tc = 1; tc <= TC; tc++) {
		ll N; scanf("%lld", &N);
		printf("Case #%d: ", tc);
		

		vector<int> d;
		for (ll NN = N; NN; NN /= 10)
			d.push_back(NN % 10);
		reverse(d.begin(), d.end());


		int i = 0;
		while (i+1 < d.size() && d[i] <= d[i+1])
			i++;

		if (i+1 == d.size()) {
			printf("%lld\n", N);
			continue;
		}

		int j = i;
		while (0 <= j-1 && d[j-1] == d[j]) j--;

		d[j]--;
		for (int t=j+1; t<d.size(); t++)
			d[t] = 9;


		
		for (int t=!d[0]; t<d.size(); t++)
			printf("%d", d[t]);
		puts("");

		







	}


	return 0;
}
