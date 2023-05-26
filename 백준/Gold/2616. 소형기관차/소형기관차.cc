#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
//#include <format>

using namespace std;

int n, m;
vector<int> nums;
vector<int> sums;
array<array<int, 50'001>, 4> dp;

int DP(int i, int j);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	// 초기화
	fill_n(&dp[0][0], 50'001 * 4, -1);

	// 입력받기
	cin >> n;
	nums.assign(n + 1, 0);
	sums.assign(n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		cin >> nums[i];
		sums[i] = sums[i - 1] + nums[i];
	}
	cin >> m;

	// dp[i][j] = i개의 기관차로 j번째 객실까지 살펴봤을때 최대로 운송할 수 있는 손님의 수
	// dp[i][j] = max(dp[i][j + 1], dp[i - 1][j - m - 1] + sums[j] - sums[j - m]);
	dp[1][m] = sums[m] - sums[0];
	cout << DP(3, n);

}

int DP(int i, int j) {
	//cout << format("dp[{}][{}] = ", i, j);

	if (i == 0 || j < m * i) {
		//cout << format("{}\n", 0);
		return 0;
	}

	if (dp[i][j] != -1) {
		//cout << format("{}\n", dp[i][j]);
		return dp[i][j];
	}

	//cout << format("max( dp[{}][{}], dp[{}][{}] + sums[{}] - sums[{}]  )\n", i, j - 1, i - 1, j - m - 1, j, j - m);
	dp[i][j] = max(DP(i, j - 1), DP(i - 1, j - m) + sums[j] - sums[j - m]);
	
	//cout << format("dp[{}][{}] = {}로 결정\n", i, j, dp[i][j]);
	return dp[i][j];
}

