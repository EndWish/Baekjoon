#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>

using namespace std;

int n;
vector<int> nums;
vector<int> dp;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	nums.assign(n, {});
	for (int& num : nums)
		cin >> num;
	
	dp.push_back(nums[0]);
	for (int i = 1; i < n; ++i) {
		auto it = ranges::lower_bound(dp, nums[i]);
		if (it != dp.end()) {
			*it = nums[i];
		}
		else {
			dp.push_back(nums[i]);
		}
	}

	cout << dp.size();

}

