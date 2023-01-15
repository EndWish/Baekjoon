#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long
#define pll pair<ll,ll>

int n, m;
vector<pll> nums;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		ll s, e;
		cin >> s >> e;
		if (s > e)	// 역방향으로 가는 인원만 체크하면 된다.
			nums.emplace_back(e, s);	// 시작과 도착위치를 바꿔 저장한다.
	}

	//문제해결
	ll ans = m;

	ranges::sort(nums);
	ll last = 0;
	for (auto [s, e] : nums) {
		if (last <= s) {
			ans += (e - s) * 2;
			last = e;
		}
		else {
			ans += max((e - last) * 2LL, 0LL);
			last = max(last, e);
		}
	}

	cout << ans;

}