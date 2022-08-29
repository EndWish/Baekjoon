#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0 ,-1,1 };

using namespace std;

int n, m, t;
int board[2][50][50];
int upper = -1, lower = -1;

bool Inside(int r, int c);
void Print();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m >> t;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> board[0][r][c];
			if (board[0][r][c] == -1) {
				if (upper == -1)
					upper = r;
				else
					lower = r;
			}
		}
	}

	//문제해결
	while (t-- > 0) {
		// 보드1 초기화
		fill_n(&board[1][0][0], 50 * 50, 0);
		board[1][upper][0] = -1;
		board[1][lower][0] = -1;

		// 미세먼지가 확산된다. 확산은 미세먼지가 있는 모든 칸에서 동시에 일어난다
		for (int r = 0; r < n; ++r) {
			for (int c = 0; c < m; ++c) {
				if (board[0][r][c] > 0) {	// 미세먼지가 있을경우
					int count = 0;
					for (int i = 0; i < 4; ++i) {
						int nr = r + dr[i];
						int nc = c + dc[i];
						if (Inside(nr, nc) && board[0][nr][nc] != -1) {	// 퍼지는 곳이 보드안이고 공기청정기가 아닐경우
							++count;
							board[1][nr][nc] += board[0][r][c] / 5;
						}
					}
					board[1][r][c] += board[0][r][c] - (board[0][r][c] / 5) * count;
				}
			}
		}
		copy(&board[1][0][0], &board[1][0][0] + 50 * 50, &board[0][0][0]);

		// 공기청정기가 작동한다
		for (int r = upper - 2; r >= 0; --r)	// 반시계-왼쪽
			board[0][r + 1][0] = board[0][r][0];
		for (int c = 1; c < m; ++c)				// 반시계-위쪽
			board[0][0][c - 1] = board[0][0][c];
		for (int r = 1; r <= upper; ++r)	// 반시계-오른쪽
			board[0][r - 1][m - 1] = board[0][r][m - 1];
		for (int c = m - 2; c >= 1; --c)
			board[0][upper][c + 1] = board[0][upper][c];

		for (int r = lower + 2; r < n; ++r)
			board[0][r - 1][0] = board[0][r][0];
		for (int c = 1; c < m; ++c)
			board[0][n - 1][c - 1] = board[0][n - 1][c];
		for (int r = n - 2; r >= lower; --r)
			board[0][r + 1][m - 1] = board[0][r][m - 1];
		for (int c = m - 2; c >= 1; --c)
			board[0][lower][c + 1] = board[0][lower][c];

		board[0][lower][1] = 0;
		board[0][upper][1] = 0;
	}

	//출력
	cout << reduce(&board[0][0][0], &board[0][0][0] + 50 * 50) + 2;

}

bool Inside(int r, int c) {
	if (r < 0 || n <= r || c < 0 || m <= c)
		return false;
	return true;
}