#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define INF numeric_limits<int>::max()

int n, k;
vector<int> coins;
int dp[10'001];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	fill_n(dp, 10'001, INF);
	dp[0] = 0;

	cin >> n >> k;
	coins.assign(n, {});
	for (int& coin : coins)
		cin >> coin;

	//문제해결
	ranges::sort(coins);
	for (int i = 1; i <= k; ++i) {
		for (int coin : coins) {
			int prevIndex = i - coin;
			if (0 <= prevIndex) {
				if (dp[prevIndex] != INF && dp[prevIndex] + 1 < dp[i]) {
					dp[i] = dp[i - coin] + 1;
				}
			}
			else {
				break;
			}
		}
	}

	//출력
	if (dp[k] == INF)
		cout << -1;
	else
		cout << dp[k];

}
