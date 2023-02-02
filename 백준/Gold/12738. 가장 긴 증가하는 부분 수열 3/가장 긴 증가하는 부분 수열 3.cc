#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long

int n;
vector<ll> nums;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	nums.assign(n, {});
	for (ll& num : nums)
		cin >> num;

	//문제해결
	vector<ll> ans;
	ans.push_back(nums[0]);
	for (int num : nums | views::drop(1)) {
		auto posIter = ranges::lower_bound(ans, num);
		if (posIter == ans.end())
			ans.push_back(num);
		else
			*posIter = num;
	}

	cout << ans.size();
	
}

