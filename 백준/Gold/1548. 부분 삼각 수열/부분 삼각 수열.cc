#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n;
vector<int> nums;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	nums.assign(n, {});
	for (int& num : nums)
		cin >> num;

	ranges::sort(nums);

	int ans = min(2, (int)nums.size());

	for (int i = 0; i < nums.size(); ++i) {
		for (int j = i + 1; j < nums.size(); ++j) {
			for (int k = j + 1; k < nums.size(); ++k) {
				if (nums[i] + nums[j] > nums[k]) {
					ans = max(ans, k - j + 2);
				}
			}
		}
	}
	cout << ans;
	
}
