#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>
//#include <format>

using namespace std;

#define MAXN 1001

array<array<int, MAXN>, MAXN> board;
array<array<int, MAXN>, MAXN> dp;
int n, m;

bool Inside(int r, int c);
int DP(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	fill_n(&dp[0][0], MAXN * MAXN, -1);

	cin >> n >> m;
	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= m; ++c) {
			cin >> board[r][c];
		}
	}

	//문제해결
	cout << DP(n, m);

	//출력

}

int DP(int r, int c) {
	if (!Inside(r, c))
		return 0;

	if (dp[r][c] != -1)
		return dp[r][c];

	dp[r][c] = board[r][c];
	dp[r][c] += max(DP(r - 1, c), DP(r, c - 1));
	return dp[r][c];
}

bool Inside(int r, int c) {
	return !(r < 1 || n < r || c < 1 || m < c);
}