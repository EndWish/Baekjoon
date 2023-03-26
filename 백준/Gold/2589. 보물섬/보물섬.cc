#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>


using namespace std;

#define pii pair<int,int>

int dr[] = { 0,0,-1,1 };
int dc[] = { -1,1,0,0 };

int n, m;
array<array<char, 50>, 50> board;
array<array<int, 50>, 50> visit;

int BFS(int sr, int sc);
bool IsInside(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	ranges::fill_n(&visit[0][0], 50 * 50, -1);
	cin >> n >> m;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> board[r][c];
		}
	}

	int ans = 0;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			if (board[r][c] == 'L') {
				ranges::fill_n(&visit[0][0], 50 * 50, -1);
				ans = max(ans, BFS(r, c));
			}
		}
	}
	cout << ans;
}


int BFS(int sr, int sc) {

	queue<pii> q;
	q.emplace(sr, sc);
	visit[sr][sc] = 0;

	while (true) {
		auto [r, c] = q.front();
		q.pop();

		for (int i = 0; i < 4; ++i) {
			int nr = r + dr[i];
			int nc = c + dc[i];

			if (IsInside(nr, nc) && board[nr][nc] == 'L' && visit[nr][nc] == -1) {
				visit[nr][nc] = visit[r][c] + 1;
				q.emplace(nr, nc);
			}
		}

		if (q.empty())
			return visit[r][c];
	}
}

bool IsInside(int r, int c) {
	return  0 <= r && r < n && 0 <= c && c < m;
}