#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>
//#include <format>

using namespace std;

#define MAXN 100'001
#define ll long long

ll n, c, w;
vector<ll> logs;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> c >> w;
	logs.assign(n, {});
	for (ll& log : logs)
		cin >> log;

	//문제해결
	ll result = 0;
	for (int cutLeng = 1; cutLeng <= 10'000; ++cutLeng) {
		ll ans = 0;

		for (ll log : logs) {
			int benefit = (log / cutLeng) * (cutLeng * w - c);
			if (log % cutLeng == 0)
				benefit += c;
			if (0 < benefit)
				ans += benefit;
		}
		result = max(result, ans);
	}

	//출력
	cout << result;

}
