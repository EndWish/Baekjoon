#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,1,0,-1 };

int n, m;
int robotR, robotC, robotD;
array<array<int, 50>, 50> board;

bool IsInside(int r, int c);
bool IsWall(int r, int c);
bool IsCleanAround(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m >> robotR >> robotC >> robotD;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> board[r][c];
		}
	}

	//문제해결
	int ans = 0;
	while (true) {
		// 1번
		if (board[robotR][robotC] == 0) {
			board[robotR][robotC] = 2;
			++ans;
		}

		// 2번
		if (IsCleanAround(robotR, robotC)) {
			int nr = robotR - dr[robotD];
			int nc = robotC - dc[robotD];
			if (IsInside(nr, nc) && !IsWall(nr, nc)) {
				robotR = nr;
				robotC = nc;
			}
			else {
				break;
			}
		}

		// 3번
		else {
			robotD = (robotD - 1 + 4) % 4;
			int nr = robotR + dr[robotD];
			int nc = robotC + dc[robotD];
			if (IsInside(nr, nc) && !IsWall(nr, nc) && board[nr][nc] == 0) {
				robotR = nr;
				robotC = nc;
			}
		}
	}
	
	cout << ans;
}

bool IsInside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}
bool IsWall(int r, int c) {
	return board[r][c] == 1;
}
bool IsCleanAround(int r, int c) {
	for (int i = 0; i < 4; ++i) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (IsInside(nr, nc) && !IsWall(nr, nc) && board[nr][nc] == 0)
			return false;
	}
	return true;
}

