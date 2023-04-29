#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int dr[] = { 0,0,-1,1 };
int dc[] = { -1,1,0,0 };

int n;
array<array<int, 100>, 100> board;
array<array<bool, 100>, 100> visit;

bool IsInside(int r, int c);
void DFS(int r, int c, int water);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	int maxHeight = 0;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			cin >> board[r][c];
			maxHeight = max(maxHeight, board[r][c]);
		}
	}

	int ans = 0;
	for (int water = 0; water < maxHeight; ++water) {
		fill_n(&visit[0][0], 100 * 100, false);
		int area = 0;

		for (int r = 0; r < n; ++r) {
			for (int c = 0; c < n; ++c) {
				if (!visit[r][c] && board[r][c] > water) {
					DFS(r, c, water);
					++area;
				}
			}
		}
		ans = max(ans, area);
	}
	cout << ans;
}

void DFS(int r, int c, int water) {
	visit[r][c] = true;
	for (int i = 0; i < 4; ++i) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (IsInside(nr, nc) && !visit[nr][nc] && board[nr][nc] > water) {
			DFS(nr, nc, water);
		}
	}
}

bool IsInside(int r, int c){
	return 0 <= r && r < n && 0 <= c && c < n;
}
