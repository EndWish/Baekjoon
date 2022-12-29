#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

using namespace std;

#define ll long long

// 거리의 합 (2399)

int n;
vector<ll> nums;
vector<ll> sums;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	nums.assign(n, {});
	sums.assign(n, {});
	for (ll& num : nums)
		cin >> num;
	
	//문제해결
	ranges::sort(nums);
	sums[0] = nums[0];
	for (int i = 1; i < n; ++i)
		sums[i] = sums[i - 1] + nums[i];

	ll ans = 0;
	for (int i = 1; i < n; ++i) {
		ans += (nums[i] * i - sums[i - 1]) * 2;
	}

	//출력
	cout << ans;

}
