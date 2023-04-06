#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n, k;
vector<int> poses;
vector<int> dists;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> k;
	poses.assign(n, {});
	for (int i = 0; i < n; ++i) {
		cin >> poses[i];
	}
	ranges::sort(poses);

	for (int i = 1; i < n; ++i) {
		dists.push_back(poses[i] - poses[i - 1]);
	}
	ranges::sort(dists);

	int ans = 0;
	for (int i = 0; i < n - k; ++i)
		ans += dists[i];

	cout << ans;
}


