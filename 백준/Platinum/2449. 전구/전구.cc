#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define INF numeric_limits<int>::max()

int n, k;
vector<int> nums;
array<array<int, 200>, 200> dp;	// dp[s][e] = nums의 인덱스 a부터 e까지를 색상nums[s]로 바꾸는데 최소 횟수

int DP(int s, int e);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> k;
	nums.assign(n, {});
	for (int& num : nums)
		cin >> num;

	ranges::fill_n(&dp[0][0], 200 * 200, -1);
	int ans = DP(0, n - 1);
	cout << ans;

}

int DP(int s, int e) {

	if (dp[s][e] != -1)
		return dp[s][e];

	if (s == e) {
		return dp[s][e] = 0;
	}

	dp[s][e] = INF;
	for (int mid = s; mid < e; ++mid) {
		if (nums[s] == nums[mid + 1]) {
			dp[s][e] = min(dp[s][e], DP(s, mid) + DP(mid + 1, e));
		}
		else {
			dp[s][e] = min(dp[s][e], DP(s, mid) + DP(mid + 1, e) + 1);
		}
	}

	return dp[s][e];
}
