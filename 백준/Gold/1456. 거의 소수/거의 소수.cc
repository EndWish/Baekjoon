#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	ll a, b;
	cin >> a >> b;

	ll ans = 0;
	const ll maxNum = 10'000'000;
	vector<bool> sieve(maxNum + 1, true);
	for (ll i = 2; i <= maxNum; ++i) {
		if (sieve[i]) {
			for (ll j = i * i; j <= maxNum; j += i) {
				sieve.at(j) = false;
			}
			for (ll j = i * i; j <= b;) {
				if (a <= j && j <= b)
					++ans;

				if (j < (b / i + 1))
					j *= i;
				else
					break;
			}
		}
	}
	cout << ans;

}
