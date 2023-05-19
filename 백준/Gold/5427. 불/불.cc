#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

struct Tuple {
	int a, b, c;
	Tuple(int a, int b, int c) : a{ a }, b{ b }, c{ c }{

	}
};

#define pii pair<int,int>

int dr[] = { 0,0,-1,1 };
int dc[] = { -1,1,0,0 };

int n, m;
array<array<char, 1000>, 1000> board;
array<array<int, 1000>, 1000> visit;


bool IsInside(int r, int c);
int BFS(queue<Tuple>& q);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t;
	cin >> t;
	while (t-- > 0) {
		queue<Tuple> q;
		fill_n(&visit[0][0], 1000000, -1);

		cin >> m >> n;

		int sr, sc;
		for (int r = 0; r < n; ++r) {
			for (int c = 0; c < m; ++c) {
				cin >> board[r][c];
				if (board[r][c] == '*') {
					q.emplace(0, r, c);
				}
				else if (board[r][c] == '@') {
					sr = r;
					sc = c;
				}
			}
		}
		visit[sr][sc] = 0;
		q.emplace(1, sr, sc);

		int result = BFS(q);
		if (result == -1) {
			cout << "IMPOSSIBLE\n";
		}
		else {
			cout << result << "\n";
		}

	}
	
}

int BFS(queue<Tuple>& q) {
	while (!q.empty()) {
		auto [type, r, c] = q.front();
		q.pop();

		// 불일경우
		if (type == 0) {
			for (int i = 0; i < 4; ++i) {
				int nr = r + dr[i];
				int nc = c + dc[i];
				if (!IsInside(nr, nc) || board[nr][nc] == '#' || board[nr][nc] == '*')
					continue;
				board[nr][nc] = '*';
				q.emplace(0, nr, nc);
			}
		}
		// 사람일 경우
		else {
			// 탈출한 경우
			if (r == 0 || r == n - 1 || c == 0 || c == m - 1) {
				return visit[r][c] + 1;
			}

			for (int i = 0; i < 4; ++i) {
				int nr = r + dr[i];
				int nc = c + dc[i];
				if (!IsInside(nr, nc) || board[nr][nc] == '#' || board[nr][nc] == '*' || visit[nr][nc] != -1)
					continue;
				visit[nr][nc] = visit[r][c] + 1;
				q.emplace(1, nr, nc);
			}
		}
	}
	return -1;
}

bool IsInside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}
