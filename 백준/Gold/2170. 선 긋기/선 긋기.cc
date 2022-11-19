#include <iostream>
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define ll long long
#define pll pair<ll,ll>

ll n;
vector<pll> lines;
ll dp = numeric_limits<ll>::min();
ll sum;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	lines.assign(n, {});
	for (auto& [s, e] : lines)
		cin >> s >> e;
	
	//문제해결
	ranges::sort(lines);
	for (auto [s, e] : lines) {
		sum += max(0LL, e - max(s, dp));
		dp = max(dp, e);
	}

	//출력
	cout << sum;
}