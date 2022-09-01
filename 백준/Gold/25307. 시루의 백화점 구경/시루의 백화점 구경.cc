#include <iostream>
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <cmath>
//#include <format>

#define MAXN 2000
#define pii pair<int,int>
#define INF numeric_limits<int>::max()

using namespace std;

int dr[] = { 1,-1,0,0 };
int dc[] = { 0,0,1,-1 };

int n, m, k;
int board[MAXN][MAXN];
int visit[MAXN][MAXN];

bool Inside(int r, int c);
void Print();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	fill_n(&visit[0][0], MAXN * MAXN, -1);
	queue<pii> dummy;

	int sr, sc;
	cin >> n >> m >> k;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> board[r][c];
			if (board[r][c] == 3) {
				dummy.emplace(r, c);
				visit[r][c] = 0;
				board[r][c] = 1;
			}
			else if (board[r][c] == 4) {
				sr = r;
				sc = c;
			}
		}
	}

	//문제해결
	while (!dummy.empty()) {
		auto [r, c] = dummy.front();
		dummy.pop();

		if (visit[r][c] == k)
			continue;

		for (int i = 0; i < 4; ++i) {
			int nr = r + dr[i];
			int nc = c + dc[i];
			if (!Inside(nr, nc) || visit[nr][nc] != -1 || board[nr][nc] == 1)
				continue;

			visit[nr][nc] = visit[r][c] + 1;
			board[nr][nc] = 1;
			dummy.emplace(nr, nc);
		}
	}

	fill_n(&visit[0][0], MAXN * MAXN, -1);
	queue<pii> q;
	visit[sr][sc] = 0;
	q.emplace(sr, sc);
	while (!q.empty()) {
		auto [r, c] = q.front();
		q.pop();

		//cout << r << " " << c << " " << visit[r][c] << "\n";

		for (int i = 0; i < 4; ++i) {
			int nr = r + dr[i];
			int nc = c + dc[i];
			if (!Inside(nr, nc) || visit[nr][nc] != -1 || board[nr][nc] == 1)
				continue;

			visit[nr][nc] = visit[r][c] + 1;
			q.emplace(nr, nc);
		}
	}

	//출력
	int ans = INF;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			if (board[r][c] == 2 && visit[r][c] != -1)
				ans = min(ans, visit[r][c]);
		}
	}

	if (ans == INF)
		cout << -1;
	else
		cout << ans;

	//Print();
}

bool Inside(int r, int c) {
	if (r < 0 || n <= r || c < 0 || m <= c)
		return false;
	return true;
}

void Print() {
	cout << "\n";
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cout << visit[r][c] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

}