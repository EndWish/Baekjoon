#include <iostream>
#include <queue>
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

int dr[] = { 1,-1,0,0 };
int dc[] = { 0,0,1,-1 };

int n, m, k;
array<array<char, 5>, 5> board;
array<array<bool, 5>, 5> visit;

int DFS(int r, int c, int depth);
bool Inside(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m >> k;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> board[r][c];
		}
	}

	//문제해결
	cout << DFS(n - 1, 0, 1);

	//출력

}

int DFS(int r, int c, int depth) {
	if (depth == k && r == 0 && c == m - 1)
		return 1;
	if (k - depth < r + (m - 1 - c))
		return 0;

	visit[r][c] = true;

	int result = 0;
	for (int i = 0; i < 4; ++i) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (Inside(nr, nc) && !visit[nr][nc] && board[nr][nc] != 'T') {
			result += DFS(nr, nc, depth + 1);
		}
	}

	visit[r][c] = false;
	return result;
}

bool Inside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}
