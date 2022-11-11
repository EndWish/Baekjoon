#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define ll long long

ll n, u;
vector<ll> nums;
vector<ll> num2s;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	nums.assign(n, {});
	for (ll& num : nums)
		cin >> num;

	//문제해결
	ll ans = 0;
	num2s.reserve(n * n);
	for (int i = 0; i < nums.size(); ++i)
		for (int j = 0; j < nums.size(); ++j)
			num2s.push_back(nums[i] + nums[j]);

	ranges::sort(nums);
	ranges::sort(num2s);
	for (int i = 0; i < nums.size(); ++i) {
		for (int j = i + 1; j < nums.size(); ++j) {
			ll target = nums[j] - nums[i];
			if (ranges::equal_range(num2s, target)) {
				ans = max(ans, nums[j]);
				break;
			}
		}
	}

	//출력
	cout << ans;
}