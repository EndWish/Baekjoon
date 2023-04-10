#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long
#define pii pair<ll,ll>
#define INF numeric_limits<ll>::max()

int n, m;
vector<pii> food;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	food.assign(n, {});
	for (auto& [cost, w] : food)
		cin >> w >> cost;

	auto pred = [](const pii& a, const pii& b) {
		if (a.first == b.first)
			return a.second > b.second;
		return a.first < b.first;
	};
	ranges::sort(food, pred);

	ll ans = INF;
	ll sumWeight = 0;
	ll cnt = 0;
	ll prevCost = -1;

	for (auto [cost, w] : food) {
		sumWeight += w;
		if (prevCost < cost) {
			cnt = 0;
		}
		++cnt;

		if (m <= sumWeight) {
			ans = min(ans, cost * cnt);
		}

		prevCost = cost;
	}

	if (ans == INF)
		cout << -1;
	else
		cout << ans << "\n";
}
