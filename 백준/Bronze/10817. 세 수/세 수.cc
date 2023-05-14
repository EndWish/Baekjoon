#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

array<int, 3> nums;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	for (int& num : nums)
		cin >> num;

	ranges::sort(nums);

	cout << nums[1];

}



