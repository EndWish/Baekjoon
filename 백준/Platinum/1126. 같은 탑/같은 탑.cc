#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <cmath>

using namespace std;

#define MAXN 50
#define GAP (500'000 / 2)
#define INF numeric_limits<int>::max()

int n;
vector<int> heights;
int dp[MAXN + 1][GAP + 1];

int DP(int use, int gap);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	heights.assign(n + 1, {});
	for (int& height : heights | views::drop(1))
		cin >> height;

	ranges::fill_n(&dp[0][0], (MAXN + 1) * (GAP + 1), -1);

	int result = DP(n, 0);
	if (result <= 0) {
		cout << -1;
	}
	else {
		cout << result;
	}

}

int DP(int use, int gap) {
	if (use == 0) {
		if (gap == 0)
			return 0;
		return -INF;
	}

	if (gap > GAP || GAP < 0) {
		return -INF;
	}

	if (dp[use][gap] != -1)
		return dp[use][gap];

	int h = heights[use];

	// 아무것도 사용하지 않은 경우 vs 탑에 쌓는 경우(낮은 탑에 쌓은 경우 vs 높은 탑에 쌓은 경우)
	dp[use][gap] = max({ DP(use - 1, gap), DP(use - 1, gap + h), DP(use - 1, abs(gap - h)) + (gap < h ? gap : h) });
	
	return dp[use][gap];
}
