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

#include <ctime>

typedef long long ll;
ll MOD = 1000000007LL;




const int SZ = 103;
int N;
vector<pair<int, int>> edges;

int calcCost() {
	int S = 0;
	for (auto e : edges)
		S += abs(e.first - e.second);
	return S;
}
int calcCost(int* p) {
	int S = 0;
	for (auto e : edges)
		S += abs(p[e.first] - p[e.second]);
	return S;
}



void randinit(int* p, int N) {
	for (int i=0; i<N; i++) p[i] = i;
	for (int i=N-1; i>=1; i--) {
		int j = rand() % (i+1);
		swap(p[j], p[i]);
	}
}
void randSwap(int*p, int N) {
	int u = rand() % N;
	int v = rand() % N;
	while (u == v) v = rand() % N;
	swap(p[u], p[v]);
}
int* genRandSwap(int* p, int N) {
	int u = rand() % N;
	int v = rand() % N;
	while (u == v) v = rand() % N;

	int* newp = new int[N];
	memcpy(newp, p, sizeof(int)*N);

	swap(newp[u], newp[v]);
	return newp;
}
bool bern(double p) {
	return rand() <= p * (1<<15);
}



void clearGraph() {
	N = 0;
	edges.clear();
}
void getInput() {
	clearGraph();
	scanf("%d", &N);
	int M; scanf("%d", &M);
	while (M--) {
		int u, v; scanf("%d%d", &u, &v);
		edges.push_back(make_pair(u, v));
	}
}
int generateRandom() {
	clearGraph();
	N = 100;
	for (int u=0; u<N; u++) for (int v=u+1; v<N; v++) {
		double randval = (double)rand() / (1<<15);
		int k = v - u;
		if (k==1 || randval < pow(0.8, k)) 
			edges.push_back(make_pair(u, v));
	}
	int ret = calcCost();

	int p[SZ]; randinit(p, N);
	for (auto &e:edges) {
		e.first = p[e.first];
		e.second = p[e.second];
	}

	return ret;
}



int ansperm[SZ];


int solveExact() {
	//assert(N <= 8);
	int q[SZ];
	for (int i=0; i<N; i++) q[i] = i;

	int ans = 1e8;
	do {
		int c = calcCost(q);
		if (ans > c) {
			ans = c;
			for (int i=0; i<N; i++) ansperm[q[i]] = i;
		}
	} while (next_permutation(q, q+N));

	return ans;
}

int solve1() {
	int best = 1e8;
	for (int z=0; z<2; z++) {
		int perm[SZ]; randinit(perm, N);
		int localbest = calcCost(perm);

		for (int zz=0; z<6; zz++) {
			int uu = -1;
			int vv = -1;

			for (int u=0; u<N; u++) for (int v=u+1; v<N; v++) {
				swap(perm[u], perm[v]);
				int c = calcCost(perm);
				swap(perm[u], perm[v]);

				if (localbest > c) {
					localbest = c;
					uu = u;
					vv = v;
				}
			}

			if (uu == -1) break;
			swap(perm[uu], perm[vv]);
		}

		best = min(best, localbest);
	}


	return best;
}

int solve2() {
	int best = 1e8;
	for (int z=0; z<30; z++) {
		int perm[SZ]; randinit(perm, N);
		int localbest = calcCost(perm);

		for (int zz=0; zz<1000; zz++) {
			int uu = -1;
			int vv = -1;

			for (int zzz=0; zzz<40; zzz++) {
				int u = rand() % N;
				int v = rand() % N;
				
				swap(perm[u], perm[v]);
				int c = calcCost(perm);
				swap(perm[u], perm[v]);

				if (localbest > c) {
					localbest = c;
					uu = u;
					vv = v;
				}
			}

			if (uu != -1) swap(perm[uu], perm[vv]);
		}

		if (best > localbest) {
			best = localbest;
			for (int i=0; i<N; i++) ansperm[perm[i]] = i;

		}
	}

	return best;
}

int solve3() {
	int best = 1e8;

	const int PPLSZ = 10;
	vector<int*> population;
	for (int i=0; i<PPLSZ; i++) {
		int *p = new int[N];
		randinit(p, N);
		best = min(best, calcCost(p));

		population.push_back(p);
	}


	for (int gen=0; gen<1000; gen++) {
		vector<pair<int, int*>> children;

		for (int* p : population) {
			for (int mut=0; mut<30; mut++) {
				int *child = genRandSwap(p, N);
				children.push_back(make_pair(calcCost(child), child));
			}
		}

		sort(children.begin(), children.end());

		for (auto p : population) delete p;
		population.clear();

		for (int i=0; i<children.size(); i++) {
			double r = pow(0.98, i) + 0.01;
			if (bern(r))
				population.push_back(children[i].second);
			else
				delete children[i].second;
		}
		if (bern(0.01))
			cout << population.size() << endl;

	}
	
	best = calcCost(population.front());
	return best;
}

int solve4() {
	int best = 1e8;
	for (int z=0; z<6; z++) {
		int perm[SZ]; randinit(perm, N);
		int localbest = calcCost(perm);

		for (int zz=0; z<20; zz++) {
			for (int u=0; u<N; u++) for (int v=u+1; v<N; v++) {
				swap(perm[u], perm[v]);
				int c = calcCost(perm);
				if (localbest > c) {
					localbest = c;
					goto EXIT;
				}
				swap(perm[u], perm[v]);
			}
			break;

			EXIT:
			int tmp;
		}

		best = min(best, localbest);
	}

	return best;
}

void test() {
	int nearopt = generateRandom(); 
	printf("nearopt: %d\n", nearopt);

	vector<int(*)()> solutions ={ solve2, };
	for (auto f : solutions) {
		time_t begin = clock();
		int val = f();
		time_t elapse = clock() - begin;

		double ratio = (double)val/nearopt;
		printf("%4lld  %5d %lf\n", elapse, val, ratio);
	}
	cout << endl;
}

void run(int tc) {
	getInput();
	int cost = N<=8 ? solveExact() : solve2();

	printf("Case #%d\n", tc);
	printf("%d\n", cost);
	for (int i=0; i<N; i++) printf("%d ", ansperm[i]);
	printf("\n");
}






int main() {
	setbuf(stdout, 0);
	int TC; scanf("%d", &TC);
	for (int tc=1; tc<=TC; tc++) {
		//run(tc);
		test();
	}

	return 0;
}