#include <iostream>
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define pii pair<int,int>
#define piiFalse make_pair(-1,-1)

using namespace std;

int dr[6] = { -1, 0, 1, -1, 0, 1 };
int dc[6] = { -1, -1, -1, 1, 1,  1 };

int c;
int n, m;
int blankSpace = 0;
char board[10][10];

vector<pii> edge[10][10];
pii visit[10][10];
bool finished[10][10];

bool Inside(int r, int c);
bool DFS(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> c;
	while (c-- > 0) {
		//초기화,입력값 받기
		blankSpace = 0;
		ranges::fill_n(&visit[0][0], 100, piiFalse);
		ranges::fill_n(&finished[0][0], 100, false);

		cin >> n >> m;
		for (int r = 0; r < n; ++r) {
			for (int c = 0; c < m; ++c) {
				cin >> board[r][c];
				if (board[r][c] == '.')
					++blankSpace;
			}
		}

		for (int r = 0; r < n; ++r) {
			for (int c = 0; c < m; c += 2) {
				edge[r][c].clear();
				if (board[r][c] == 'x')
					continue;
				
				for (int i = 0; i < 6; ++i) {
					int nr = r + dr[i];
					int nc = c + dc[i];
					if (Inside(nr, nc) && board[nr][nc] == '.') {
						edge[r][c].emplace_back(nr, nc);
					}
				}
				
			}
		}

		//문제해결
		int matching = 0;
		for (int r = 0; r < n; ++r) {
			for (int c = 0; c < m; c += 2) {
				if (board[r][c] == 'x')
					continue;
				
				ranges::fill_n(&finished[0][0], 100, false);
				if (DFS(r, c)) {
					++matching;
				}

			}
		}

		//출력
		cout << blankSpace - matching << "\n";

	}
}

bool Inside(int r, int c) {
	if (r < 0 || n <= r || c < 0 || m <= c)
		return false;
	return true;
}

bool DFS(int r, int c) {
	for (int i = 0; i < edge[r][c].size(); ++i) {
		auto [nr, nc] = edge[r][c][i];
		if (!finished[nr][nc]) {
			finished[nr][nc] = true;
			if (visit[nr][nc] == piiFalse || DFS(visit[nr][nc].first, visit[nr][nc].second)) {	// 아직 아무도 방문하지 않았을 경우
				visit[nr][nc] = { r, c };
				return true;
			}
		}
	}
	return false;
}
