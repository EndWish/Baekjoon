#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long
#define pii pair<int,int>
#define MAXN 20

enum State {
	horizontally,
	vertically,
	diagonally
};

array<vector<pii>, 3> deltaPos{
	vector<pii>{ {0,0}, {0,1}},
	vector<pii>{ {0,0}, {1,0}},
	vector<pii>{ {0,0}, {0,1}, {1,0}, {1,1}},
};

int n;
array<array<int, MAXN>, MAXN> board;
array<array<array<int, 3>, MAXN>, MAXN> dp;

int DP(int r, int c, State state);
bool IsInside(int r, int c);
bool isWall(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	ranges::fill_n(&(dp[0][0][0]), MAXN * MAXN * 3, -1);

	cin >> n;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			cin >> board[r][c];
		}
	}

	dp[0][0][horizontally] = 1;
	
	//문제해결
	cout << DP(n - 2, n - 1, vertically) + DP(n - 1, n - 2, horizontally) + DP(n - 2, n - 2, diagonally);

}

int DP(int r, int c, State state) {
	
	// dp로 이미 계산한 경우
	if (IsInside(r, c) && dp[r][c][state] != -1) {
		return dp[r][c][state];
	}

	// 벽이 있어서 불가능한 경우
	for (auto [dr, dc] : deltaPos[state]) {
		int nr = r + dr;
		int nc = c + dc;
		if (!IsInside(nr, nc) || isWall(nr, nc)) {
			if (IsInside(r, c)) {
				dp[r][c][state] = 0;
			}
			return 0;
		}
	}

	// 이전 단계에서 가능한 경우들
	if (state == horizontally) {
		dp[r][c][state] = DP(r - 1, c - 1, diagonally) + DP(r, c - 1, horizontally);
	}
	else if (state == vertically) {
		dp[r][c][state] = DP(r - 1, c - 1, diagonally) + DP(r - 1, c, vertically);
	}
	else if (state == diagonally) {
		dp[r][c][state] = DP(r - 1, c - 1, diagonally) + DP(r - 1, c, vertically) + DP(r, c - 1, horizontally);
	}

	return dp[r][c][state];

}

bool IsInside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < n;
}
bool isWall(int r, int c) {
	return board[r][c] == 1;
}
