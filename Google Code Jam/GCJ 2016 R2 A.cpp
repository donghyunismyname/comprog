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





// P R S
int N, R, P, S;
int c0, c1, c2;

struct Cnt {
	int p, r, s;

	bool equal(int P, int R, int S) {
		return p == P && r == R && s == S;
	}
};


vector<char> ansP[13];
Cnt cntP[13];

vector<char> ansR[13];
Cnt cntR[13];

vector<char> ansS[13];
Cnt cntS[13];


char temp[5003];
void mySortRecursive(int b, int e) {
	if (b + 1 == e) return;

	int mid = b + (e - b) / 2;
	mySortRecursive(b, mid);
	mySortRecursive(mid, e);

	if (strncmp(temp + b, temp + mid, (e - b) / 2) <= 0) return;

	for (int i = 0; i < (e - b) / 2; i++) {
		swap(temp[b + i], temp[mid + i]);
	}
}


void mySort(vector<char> &arr) {
	for (int i = 0; i < arr.size(); i++) temp[i] = arr[i];
	mySortRecursive(0, arr.size());
	for (int i = 0; i < arr.size(); i++) arr[i] = temp[i];
}








int main() {

	freopen("A-large.in", "r", stdin);
	freopen("output.txt", "w", stdout);


	ansP[0].push_back('P');
	cntP[0].p = 1;
	for (int i = 1; i <= 12; i++) {
		for (char c : ansP[i - 1]) {
			switch (c) {
			case 'P': ansP[i].push_back('P'); ansP[i].push_back('R'); break;
			case 'R': ansP[i].push_back('R'); ansP[i].push_back('S'); break;
			case 'S': ansP[i].push_back('P'); ansP[i].push_back('S'); break;
			}
		}
		cntP[i].p = cntP[i - 1].p + cntP[i - 1].s;
		cntP[i].r = cntP[i - 1].r + cntP[i - 1].p;
		cntP[i].s = cntP[i - 1].s + cntP[i - 1].r;
	}


	ansR[0].push_back('R');
	cntR[0].r = 1;
	for (int i = 1; i <= 12; i++) {
		for (char c : ansR[i - 1]) {
			switch (c) {
			case 'P': ansR[i].push_back('P'); ansR[i].push_back('R'); break;
			case 'R': ansR[i].push_back('R'); ansR[i].push_back('S'); break;
			case 'S': ansR[i].push_back('P'); ansR[i].push_back('S'); break;
			}
		}
		cntR[i].r = cntP[i].p;
		cntR[i].s = cntP[i].r;
		cntR[i].p = cntP[i].s;
	}




	ansS[0].push_back('S');
	cntS[0].s = 1;
	for (int i = 1; i <= 12; i++) {
		for (char c : ansS[i - 1]) {
			switch (c) {
			case 'P': ansS[i].push_back('P'); ansS[i].push_back('R'); break;
			case 'R': ansS[i].push_back('R'); ansS[i].push_back('S'); break;
			case 'S': ansS[i].push_back('P'); ansS[i].push_back('S'); break;
			}
		}
		cntS[i].s = cntP[i].p;
		cntS[i].p = cntP[i].r;
		cntS[i].r = cntP[i].s;
	}

	FOR(i, 13) mySort(ansP[i]);
	FOR(i, 13) mySort(ansR[i]);
	FOR(i, 13) mySort(ansS[i]);

	

	/*
	for (char c : ansP[1]) cout << c;
	cout << endl;
	for (char c : ansP[2]) cout << c;
	cout << endl;
	puts("hello");
	*/







	int TC; cin >> TC;
	for (int tc = 1; tc <= TC; tc++) {
		printf("Case #%d: ", tc);

		cin >> N >> R >> P >> S;
		c0 = P;
		c1 = R;
		c2 = S;


		int minval = min({ c0, c1, c2 });
		int maxval = max({ c0, c1, c2 });
		if (minval + 1 != maxval) {
			puts("IMPOSSIBLE");
			continue;
		}



		if (cntP[N].equal(P, R, S)) {
			for (char c : ansP[N]) cout << c;
			//puts("");  puts("P");
		}
		if (cntR[N].equal(P, R, S)) {
			for (char c : ansR[N]) cout << c;
			//puts(""); puts("R");
		}
		if (cntS[N].equal(P, R, S)) {
			for (char c : ansS[N]) cout << c;
			//puts(""); puts("S");
		}
		

		cout << endl;

	}


	return 0;
}
