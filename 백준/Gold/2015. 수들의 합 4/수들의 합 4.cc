#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long

ll n, k;
array<ll, 200'000> sums;
unordered_map<ll, ll> prevSums;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	// 누적합dp와 스위핑을 이용하여 빠르게 풀 수 있다.

	cin >> n >> k;
	cin >> sums[0];
	for (int i = 1; i < n; ++i) {
		cin >> sums[i];
		sums[i] += sums[i - 1];
	}

	ll ans = 0;
	for (int i = 0; i < n; ++i) {
		ll sum = sums[i];

		if (sum == k) {
			++ans;
		}

		if (prevSums.contains(sum - k)) {
			ans += prevSums[sum - k];
		}

		++prevSums[sum];
	}

	cout << ans;

}
