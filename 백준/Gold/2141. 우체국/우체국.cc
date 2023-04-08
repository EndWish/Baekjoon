#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long
#define pll pair<ll,ll>

ll n;
vector<pll> cities;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	ll nPeople = 0;

	cin >> n;
	cities.assign(n, {});
	for (auto& [x, a] : cities) {
		cin >> x >> a;
		nPeople += a;
	}

	ranges::sort(cities);

	ll count = 0;
	ll index = 0;
	while (true) {
		count += cities[index].second;
		if (nPeople <= count * 2) {
			break;
		}
		++index;
	}

	cout << cities[index].first;
}
