#include <iostream>
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>
//#include <numeric>
//#include <format>

using namespace std;

#define MAXN 100
#define tiii tuple<int,int,int>

int mapping[] = { 0, 1,3,2,0 };	// 동서남북
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

int m, n;
bool board[MAXN][MAXN];
int visit[MAXN][MAXN][4];
int sr, sc, sd;
int er, ec, ed;
queue<tiii> q;

bool Inside(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	fill_n(visit[0][0], MAXN * MAXN * 4, -1);

	cin >> m >> n;	// 세로, 가로
	for (int r = 0; r < m; ++r)
		for (int c = 0; c < n; ++c)
			cin >> board[r][c];
	cin >> sr >> sc >> sd;
	cin >> er >> ec >> ed;
	--sr; --sc;
	--er; --ec;
	sd = mapping[sd];
	ed = mapping[ed];

	//문제해결
	q.emplace(sr, sc, sd);
	visit[sr][sc][sd] = 0;
	while (!q.empty()) {
		auto [r, c, d] = q.front();
		q.pop();

		// 회전하기
		int nd = (d + 1) % 4;
		if (visit[r][c][nd] ==  -1) {
			q.emplace(r, c, nd);
			visit[r][c][nd] = visit[r][c][d] + 1;
		}
		nd = (d + 3) % 4;
		if (visit[r][c][nd] == -1) {
			q.emplace(r, c, nd);
			visit[r][c][nd] = visit[r][c][d] + 1;
		}

		// 전진하기
		int nr, nc;
		for (int k = 1; k <= 3; ++k) {
			nr = r + dr[d] * k;
			nc = c + dc[d] * k;
			if (!Inside(nr, nc) || board[nr][nc])
				break;

			if (visit[nr][nc][d] == -1) {
				q.emplace(nr, nc, d);
				visit[nr][nc][d] = visit[r][c][d] + 1;
			}
		}

		

	}

	//출력
	cout << visit[er][ec][ed];

}

bool Inside(int r, int c) {
	if (r < 0 || m <= r || c < 0 || n <= c)
		return false;
	return true;
}
