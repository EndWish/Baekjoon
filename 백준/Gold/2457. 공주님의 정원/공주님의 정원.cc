#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define pii pair<int,int>
#define ppp pair<pii, pii>

int n;
vector<ppp> flowers;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	flowers.assign(n, {});
	for (auto& [s, e] : flowers) {
		cin >> s.first >> s.second;
		cin >> e.first >> e.second;
	}

	ranges::sort(flowers);

	int ans = 0;
	pii deadline = { 3, 1 };
	int i = 0;
	while (i < n) {
		pii maxDeadline = deadline;
		while (i < n && flowers[i].first <= deadline) {
			maxDeadline = max(maxDeadline, flowers[i].second);
			++i;
		}

		// 더이상 갱신이 안되는 경우
		if (maxDeadline == deadline) {
			break;
		}

		++ans;
		deadline = maxDeadline;

		if (make_pair(12, 1) <= deadline) {
			i = n;
			break;
		}

	}

	if (i == n && make_pair(12, 1) <= deadline) {
		cout << ans;
	}
	else {
		cout << 0;
	}

}

