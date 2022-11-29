#include <iostream>
#include <array>
#include <queue>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define ll long long

int n;
array<array<ll, 21>, 101> dp;
vector<int> nums;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	nums.assign(n, {});
	for (int& num : nums)
		cin >> num;

	//문제해결
	++dp[0][nums[0]];
	for (int i = 1; i < n - 1; ++i) {
		int offset = nums[i];
		for (int j = 0; j <= 20; ++j) {
			if (j + offset <= 20) {
				dp[i][j + offset] += dp[i - 1][j];
			}
			if (j - offset >= 0) {
				dp[i][j - offset] += dp[i - 1][j];
			}
		}

		//for (int j = 0; j <= 20; ++j) {
		//	cout << dp[i][j] << " ";
		//}
		//cout << "\n";

	}

	//출력
	cout << dp[n - 2][nums[n - 1]];

}