#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define ll long long
#define INF numeric_limits<ll>::max()

ll n, t;
vector<ll> nums;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;

	//문제해결
	for (int i = 0; i < n; ++i) {
		cin >> t;
		nums.assign(t, {});
		for (ll& num : nums)
			cin >> num;

		ranges::sort(nums);
		ll ans = INF;

		auto begin = nums.begin();
		while (true) {
			auto end = ranges::upper_bound(nums, *begin);

			if (ranges::distance(begin, end) > nums.size() / 2) {	//과반수 이상을 경우
				ans = *begin;
				break;
			}

			begin = end;
			if (end == nums.end())
				break;
		}


		if (ans == INF)
			cout << "SYJKGW";
		else
			cout << ans;
		cout << "\n";

	}

	//출력

}
