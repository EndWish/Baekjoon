#include <iostream>
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define MAXN 100

int dr[] = { 1,-1,0,0 };
int dc[] = { 0,0,1,-1 };

int n, m, k;
array<array<bool, MAXN>, MAXN> board;
array<array<bool, MAXN>, MAXN> visit;

bool Inside(int r, int c);
int DFS(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m >> k;
	for (int i = 0; i < k; ++i) {
		int r, c;
		cin >> r >> c;
		--r; --c;
		board[r][c] = true;
	}
	
	//문제해결
	int ans = 0;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			if (!visit[r][c] && board[r][c])
				ans = max(ans, DFS(r, c));
		}
	}


	//출력
	cout << ans;

}

bool Inside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}

int DFS(int r, int c) {
	visit[r][c] = true;

	int result = 1;
	for (int i = 0; i < 4; ++i) {
		int nr = r + dr[i];
		int nc = c + dc[i];

		if (Inside(nr, nc) && board[nr][nc] && !visit[nr][nc]) {
			result += DFS(nr, nc);
		}
	}
	return result;
}
