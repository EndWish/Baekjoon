#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>

using namespace std;

#define offset 10000

int n;
vector<int> nums;
array<int, 20001> dp;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	nums.assign(n, {});
	for (int& num : nums) {
		cin >> num;
		++dp[num + offset];
	}

	//ranges::sort(nums);

	long long ans = 0;
	for (int i = 0; i < nums.size(); ++i) {
		for (int j = i + 1; j < nums.size(); ++j) {
			int a = nums[i];
			int b = nums[j];
			int wantNum = -(a + b);

			if (-offset <= wantNum && wantNum <= offset) {
				ans += dp[wantNum + offset];
				if (a == wantNum)
					--ans;
				if (b == wantNum)
					--ans;
			}

		}
	}

	ans /= 3;

	cout << ans;
}
