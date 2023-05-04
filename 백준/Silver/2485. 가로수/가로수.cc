#include <iostream>
#include <vector>
#include <string>
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

	int minLength = nums[1] - nums[0];
	for (int i = 0; i < nums.size() - 1; ++i) {
		int diff = nums[i + 1] - nums[i];
		minLength = gcd(minLength, diff);
	}

	int totalNumTree = (nums[nums.size() - 1] - nums[0]) / minLength + 1;
	cout << totalNumTree - nums.size();

}

