#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int dr[] = { 0,0,1,-1, -1, 1, 1, -1 };
int dc[] = { 1,-1,0,0, 1, 1, -1, -1 };

int n, m;
array<array<int, 100>, 100> board;
array<array<bool, 100>, 100> visit;

bool DFS(int r, int c);
bool IsInside(int r, int c);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> board[r][c];
		}
	}

	int ans = 0;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			if (!visit[r][c]) {
				if (DFS(r, c))
					++ans;
			}
		}
	}

	cout << ans;
}

bool DFS(int r, int c) {
	visit[r][c] = true;

	bool result = true;
	for (int i = 0; i < 8; ++i) {
		int nr = r + dr[i];
		int nc = c + dc[i];

		if (!IsInside(nr, nc))
			continue;

		if (board[nr][nc] > board[r][c])
			result = false;
		else if (board[nr][nc] == board[r][c] && !visit[nr][nc]) {
			if(!DFS(nr, nc))
				result = false;
		}
	}
	return result;
}

bool IsInside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}