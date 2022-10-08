#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define ll long long

int dr[] = { 1,0 };
int dc[] = { 0,1 };

int n;
array<array<ll, 100>, 100> board;
array<array<ll, 100>, 100> dp;

bool Inside(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			cin >> board[r][c];
		}
	}

	//문제해결
	dp[0][0] = 1;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			if (board[r][c] == 0)
				continue;

			for (int i = 0; i < 2; ++i) {
				int nr = r + dr[i] * board[r][c];
				int nc = c + dc[i] * board[r][c];

				if (!Inside(nr, nc))
					continue;

				dp[nr][nc] += dp[r][c];
			}
		}
	}

	//출력
	cout << dp[n - 1][n - 1];

}

bool Inside(int r, int c) {
	if (r < 0 || n <= r || c < 0 || n <= c)
		return false;
	return true;
}
