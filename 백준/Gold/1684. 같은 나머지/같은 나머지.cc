#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n;
vector<int> nums;
vector<int> subs;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	nums.assign(n, {});
	for (int& num : nums)
		cin >> num;

	ranges::sort(nums);

	subs.assign(nums.size() - 1, {});
	for (int i = 0; i < subs.size(); ++i) {
		subs[i] = nums[i + 1] - nums[i];
	}

	int result = subs[0];
	for (int i = 0; i < subs.size(); ++i) {
		result = gcd(result, subs[i]);
	}

	cout << result;

}


