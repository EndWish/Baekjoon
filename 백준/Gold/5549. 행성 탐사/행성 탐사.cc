#include <iostream>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define MAXN 1'001

char land[3] = { 'J', 'O', 'I' };

int m, n, k;
array<array<char, MAXN>, MAXN> board;
array<array<array<int, MAXN>, MAXN>, 3> dp;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m >> k;
	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= m; ++c) {
			cin >> board[r][c];
			for (int i = 0; i < 3; ++i) {
				dp[i][r][c] = dp[i][r - 1][c] + dp[i][r][c - 1] - dp[i][r - 1][c - 1];
				if (board[r][c] == land[i]) {
					++dp[i][r][c];
				}
			}
		}
	}

	//문제해결
	int r1, c1, r2, c2;
	for (int i = 0; i < k; ++i) {
		cin >> r1 >> c1 >> r2 >> c2;
		for (int j = 0; j < 3; ++j) {
			int num = dp[j][r2][c2] - dp[j][r2][c1 - 1] - dp[j][r1 - 1][c2] + dp[j][r1 - 1][c1 - 1];
			cout << num << " ";
		}
		cout << "\n";
	}

	//출력

}


