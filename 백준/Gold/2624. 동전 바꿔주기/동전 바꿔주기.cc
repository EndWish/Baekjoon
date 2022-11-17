#include <iostream>
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define pii pair<int,int>

int t, k;
vector<pii> coins;
array<array<int, 10'001>, 2> dp;	// [layer][cost]

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> t >> k;
	coins.assign(k, {});
	for (auto& [p, n] : coins)
		cin >> p >> n;
	
	//문제해결
	dp[0][0] = 1;
	for (auto [p, n] : coins) {
		for (int i = 1; i <= n; ++i) {	// 동전의 개수
			
			for (int j = 0; j <= t; ++j) {
				if (0 <= j - p * i) {
					dp[1][j] += dp[0][j - p * i];
				}
			}

		}
		ranges::copy(dp[1], dp[0].begin());
		dp[0][0] = 1;
	}

	//출력
	cout << dp[0][t];

}