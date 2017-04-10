/*
Google Code Jam 2017
Qualification Round
D. Fashion Show
*/
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;




struct BipartiteMatching {
	static const int ARRAYSIZE = 203;
	vector<int> adj[ARRAYSIZE];
	int backMatch[ARRAYSIZE];

	//set<int> del;
	bool visited[ARRAYSIZE];
	bool dfs(int here) {
		//if (del.find(here) != del.end()) return false;
		if (visited[here]) return false;
		visited[here] = true;

		for (int there : adj[here]) {
			//if (del.find(there) != del.end()) continue;
			if (backMatch[there] == -1 || dfs(backMatch[there])) {
				backMatch[there] = here;
				return true;
			}
		}
		return false;
	}

	int solve() {
		memset(backMatch, -1, sizeof(backMatch));

		int matchCnt = 0;
		for (int i = 0; i<ARRAYSIZE; i++) {
			memset(visited, 0, sizeof(visited));
			matchCnt += dfs(i);
		}
		return matchCnt;
	}

	void clear() {
		for (int i = 0; i < ARRAYSIZE; i++)
			adj[i].clear();
	}
} bm;




int N, M;
char boardOld[103][103];
char board[103][103];

int main() {
	freopen("D-large.in", "r", stdin);
	freopen("output.txt", "w", stdout);

	int TC; scanf("%d", &TC);
	for (int tc = 1; tc <= TC; tc++) {
		memset(boardOld, 0, sizeof(board));
		memset(board, 0, sizeof(board));
		bm.clear();

		scanf("%d%d", &N, &M);

		vector<pair<int, int>> rook, bishop;
		for (int zz = 0; zz < M; zz++) {
			char marker[10]; scanf("%s", marker);
			int i, j; scanf("%d%d", &i, &j);
			boardOld[i][j] = board[i][j] = marker[0];

			if (marker[0] == 'o' || marker[0] == 'x')
				rook.push_back(make_pair(i, j));
			if (marker[0] == 'o' || marker[0] == '+')
				bishop.push_back(make_pair(i+j, i-j+N));
		}


		{
			bool iOccupied[103] = {};
			bool jOccupied[103] = {};
			for (auto p : rook)
				iOccupied[p.first] = true,
				jOccupied[p.second] = true;

			int i = 1, j = 1;
			for (int zz=0; zz<N - rook.size(); zz++) {
				while (iOccupied[i]) i++;
				while (jOccupied[j]) j++;
				board[i][j] = board[i][j] ? 'o' : 'x';
				i++, j++;
			}
		}
		

		{
			bool dead1[203] = {};
			bool dead2[203] = {};
			for (auto p : bishop)
				dead1[p.first] = true,
				dead2[p.second] = true;

			for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) {
				int t1 = i + j;
				int t2 = i - j + N;
				if (!dead1[t1] && !dead2[t2])
					bm.adj[t1].push_back(t2);
			}
			bm.solve();

			for (int t2 = 0; t2 <= 2 * N; t2++) if (bm.backMatch[t2] != -1) {
				int t1 = bm.backMatch[t2];
				int i = (t1 + t2 - N) / 2;
				int j = t1 - i;
				board[i][j] = board[i][j] ? 'o' : '+';
			}
		}


		
		vector<pair<char, pair<int, int>>> changes;
		int score = 0;
		for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) if (board[i][j]) {
			score += board[i][j] == 'o' ? 2 : 1;

			if (boardOld[i][j] != board[i][j])
				changes.push_back(make_pair(board[i][j], make_pair(i, j)));
		}


		
		printf("Case #%d: ", tc);
		printf("%d %d\n", score, (int)changes.size());
		for (auto p : changes)
			printf("%c %d %d\n", p.first, p.second.first, p.second.second);

	}




	return 0;
}
