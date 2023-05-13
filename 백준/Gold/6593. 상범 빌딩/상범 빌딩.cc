#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

struct Tuple {
	int l, r, c;

	Tuple() {
		l = -1;
		r = -1;
		c = -1;
	};
	Tuple(int l, int r, int c) : l{ l }, r{ r }, c{ c } {
	}
};

int dl[] = { 0,0,0,0, 1, -1 };
int dr[] = { 0,0,1, -1,0,0 };
int dc[] = { 1, -1,0,0,0,0 };

int length, row, col;
array<array<array<char, 30>, 30>, 30> board;
array<array<array<int, 30>, 30>, 30> visit;

int el, er, ec;

int BFS(int sl, int sr, int sc);
bool IsInside(int l, int r, int c);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	while (cin >> length >> row >> col) {
		if (length == 0 && row == 0 && col == 0)
			break;

		// 입력받기
		int sl = -1, sr = -1, sc = -1;
		for (int l = 0; l < length; ++l) {
			for (int r = 0; r < row; ++r) {
				for (int c = 0; c < col; ++c) {
					cin >> board[l][r][c];
					if (board[l][r][c] == 'S') {
						sl = l;
						sr = r;
						sc = c;
					}
					else if (board[l][r][c] == 'E') {
						el = l;
						er = r;
						ec = c;
					}
				}
			}
		}

		// BFS수행
		int result = BFS(sl, sr, sc);
		if (result == -1) {
			cout << "Trapped!\n";
		}
		else {
			cout << "Escaped in " << result << " minute(s).\n";
		}
	}

}

int BFS(int sl, int sr, int sc) {
	ranges::fill_n(&visit[0][0][0], 30 * 30 * 30, -1);

	queue<Tuple> q;
	q.emplace(sl, sr, sc);
	visit[sl][sr][sc] = 0;
	while (!q.empty()) {
		auto [l, r, c] = q.front();
		q.pop();

		if (l == el && r == er && c == ec) {
			return visit[l][r][c];
		}

		for (int i = 0; i < 6; ++i) {
			int nl = l + dl[i];
			int nr = r + dr[i];
			int nc = c + dc[i];
			if (!IsInside(nl, nr, nc) || visit[nl][nr][nc] != -1 || board[nl][nr][nc] == '#')
				continue;

			visit[nl][nr][nc] = visit[l][r][c] + 1;
			q.emplace(nl, nr, nc);
		}
	}

	return -1;
}

bool IsInside(int l, int r, int c) {
	return 0 <= l && l < length && 0 <= r && r < row && 0 <= c && c < col;
}
