#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <cmath>

using namespace std;

#define ll long long

ll n;
vector<ll> nums;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	nums.assign(n, {});
	for (ll& num : nums)
		cin >> num;
	
	ranges::sort(nums);

	ll ans = 0;
	for (ll i = 0; i < n; ++i)
		ans += abs((i + 1) - nums[i]);

	cout << ans;

}
