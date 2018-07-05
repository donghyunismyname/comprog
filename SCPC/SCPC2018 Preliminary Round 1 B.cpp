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



bool ispal[10333];
vector<int> pals;
void precalc() {
	ispal[0] = true;
	for (int x=1; x<=10000; x++) {
		vector<int> digits;
		for (int val=x; val; val/=10) {
			digits.push_back(val%10);
		}

		int lo = 0;
		int hi = digits.size() - 1;
		ispal[x] = true;
		while (lo < hi) {
			if (digits[lo] != digits[hi]) {
				ispal[x] = false;
				break;
			}
			lo++;
			hi--;
		}

		//printf("%d %d\n", x, ispal[x]);
	}

	for (int x=0; x<=10000; x++) if (ispal[x]) 
		pals.push_back(x);
}



int main() {
	precalc();
	setbuf(stdout, 0);
	int TC; scanf("%d", &TC);
	for (int tc=1; tc<=TC; tc++) {
		int num; scanf("%d", &num);


		vector<int> ans;
		for (int a : pals) {
			if (ans.size()) break;
			if (num < a) break;
			for (int b : pals) {
				if (ans.size()) break;
				if (num < a + b) break;

				if (ispal[num - a - b])
					ans ={ a, b, num-a-b };
			}
		}

		sort(ans.begin(), ans.end());
		reverse(ans.begin(), ans.end());

		while (ans.size() >= 1 && ans.back() == 0) ans.pop_back();

		printf("Case #%d\n", tc);
		printf("%d ", ans.size());
		for (int a : ans) printf("%d ", a);
		printf("\n");


	}

	return 0;
}

