#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

#include <random>

using namespace std;

#define MAXN 1000
#define INTMIN numeric_limits<int>::min()

enum DIR {
	fromUp, fromLeft, fromRight
};

int n, m;
array<array<int, MAXN>, MAXN> board;
array<array<array<int, 3>, MAXN>, MAXN> dp;
array<array<array<bool, 3>, MAXN>, MAXN> visit;

int DP(int r, int c, DIR dir);

random_device rd;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> board[r][c];

			//uniform_int_distribution<int> uid(-100, 100);
			//board[r][c] = uid(rd);
			//cout << board[r][c] << " ";
		}
		//cout << "\n";
	}

	//문제해결
	cout << max({ DP(n - 1, m - 1, fromUp), DP(n - 1, m - 1, fromLeft) });
	
}

int DP(int r, int c, DIR dir) {
	if (r == 0 && c == 0)	// 시작 지점일 경우
		return board[r][c];

	if ((r == 0 && dir == fromUp) || (c == 0 && dir == fromLeft) || (c == m - 1 && dir == fromRight))
		return INTMIN;

	if (visit[r][c][dir])	// 이미 방문을 한 곳일 경우
		return dp[r][c][dir];
	visit[r][c][dir] = true;

	int nr = r;
	int nc = c;
	if (dir == fromUp) {
		nr = r - 1;
		dp[r][c][dir] = max({ DP(nr, nc, fromUp), DP(nr, nc, fromLeft) , DP(nr, nc, fromRight) });
	}
	else if (dir == fromLeft) {
		nc = c - 1;
		dp[r][c][dir] = max({ DP(nr, nc, fromUp), DP(nr, nc, fromLeft) });
	}
	else if (dir == fromRight) {
		nc = c + 1;
		dp[r][c][dir] = max({ DP(nr, nc, fromUp), DP(nr, nc, fromRight) });
	}

	if (dp[r][c][dir] != INTMIN) {
		dp[r][c][dir] += board[r][c];
	}
	return dp[r][c][dir];
}
