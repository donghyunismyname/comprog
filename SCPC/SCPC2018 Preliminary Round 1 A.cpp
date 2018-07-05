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



int A[200333];


int main() {
	setbuf(stdout, 0);
	int TC; scanf("%d", &TC);
	for (int tc=1; tc<=TC; tc++) {

		int N, K; scanf("%d%d", &N, &K);
		for (int i=0; i<N; i++) scanf("%d", A+i);
		sort(A, A+N);

		int maxcnt = 0;
		int cnt = 0;

		for (int hi=0, lo=0; hi<N; hi++) {
			cnt += 1;
			while (A[lo] < A[hi]-K) lo++, cnt--;

			maxcnt = max(cnt, maxcnt);
			//printf("[debug] %d\n", cnt);
		}

		printf("Case #%d\n", tc);
		printf("%d\n", maxcnt);
	}

	return 0;
}





