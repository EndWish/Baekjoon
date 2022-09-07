#include <iostream>
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define pii pair<int,int>

using namespace std;

int n, m;
int board[1024][1024];
int dp[1024][1024];

bool Inside(int r, int c);
int DP(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			cin >> board[r][c];
			dp[r][c] = DP(r - 1, c) + DP(r, c - 1) - DP(r - 1, c - 1) + board[r][c];
		}
	}

	//문제해결
	int r1, c1, r2, c2;
	for (int i = 0; i < m; ++i) {
		cin >> r1 >> c1;
		cin >> r2 >> c2;
		--r1; --c1;
		--r2; --c2;

		cout << DP(r2, c2) - DP(r1 - 1, c2) - DP(r2, c1 - 1) + DP(r1 - 1, c1 - 1) << "\n";

	}

	//출력

}

bool Inside(int r, int c) {
	if (r < 0 || n <= r || c < 0 || n <= c)
		return false;
	return true;
}

int DP(int r, int c) {
	if (Inside(r, c))
		return dp[r][c];
	return 0;
}
