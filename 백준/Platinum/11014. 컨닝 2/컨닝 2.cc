#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXN 80
#define pii pair<int,int>
#define piinull make_pair(-1,-1)

int dr[6] = { -1, 0, 1, -1 , 0, 1 };
int dc[6] = { -1, -1, -1, 1 , 1, 1 };

int t, n, m, nSeat;
array<array<char, MAXN>, MAXN> board;
array<array<vector<pii>, MAXN>, MAXN> edges;
array<array<pii, MAXN>, MAXN> visit;
array<array<bool, MAXN>, MAXN> finished;

bool Inside(int r, int c);
bool DFS(pii rc);
bool DFS(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


	cin >> t;
	while (t-- > 0) {
		//초기화,입력값 받기
		ranges::fill_n(&edges[0][0], MAXN * MAXN, vector<pii>{});
		ranges::fill_n(&visit[0][0], MAXN * MAXN, piinull);

		nSeat = 0;
		cin >> n >> m;
		for (int r = 0; r < n; ++r) {
			for (int c = 0; c < m; ++c) {
				cin >> board[r][c];
				if (board[r][c] == '.')
					++nSeat;
			}
		}

				

		for (int r = 0; r < n; ++r) {
			for (int c = 0; c < m; c += 2) {
				if (board[r][c] == 'x')
					continue;

				for (int i = 0; i < 6; ++i) {
					int nr = r + dr[i];
					int nc = c + dc[i];
					if (Inside(nr, nc) && board[nr][nc] == '.') {
						edges[r][c].emplace_back(nr, nc);
					}
				}
			}
		}	

		//문제해결
		int ans = nSeat;
		for (int r = 0; r < n; ++r) {
			for (int c = 0; c < m; c += 2) {
				if (board[r][c] == 'x')
					continue;

				ranges::fill_n(&finished[0][0], MAXN * MAXN, false);
				if (DFS(r, c))
					--ans;
			}
		}

		cout << ans << "\n";

	}
}

bool Inside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}
bool DFS(pii rc) {
	return DFS(rc.first, rc.second);
}
bool DFS(int r, int c) {
	for (auto [nr, nc] : edges[r][c]) {
		if (visit[nr][nc] == piinull) {
			visit[nr][nc] = { r, c };
			return true;
		}
		else if (!finished[nr][nc]) {
			finished[nr][nc] = true;
			if (DFS(visit[nr][nc])) {
				visit[nr][nc] = { r, c };
				return true;
			}
		}
	}
	return false;
}
