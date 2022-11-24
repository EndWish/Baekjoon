#include <iostream>
#include <unordered_set>
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

unordered_set<int> twoSum;
int n;
vector<int> nums;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	nums.assign(n, {});
	for (int& num : nums)
		cin >> num;

	//문제해결
	int ans = 0;
	twoSum.insert(nums[0] + nums[0]);
	for (int i = 1; i < nums.size(); ++i) {
		for (int j = 0; j < i; ++j) {
			if (twoSum.contains(nums[i] - nums[j])) {
				++ans;
				break;
			}
		}
		for (int j = 0; j <= i; ++j) {
			twoSum.insert(nums[j] + nums[i]);
		}
	}

	//출력
	cout << ans;

}
