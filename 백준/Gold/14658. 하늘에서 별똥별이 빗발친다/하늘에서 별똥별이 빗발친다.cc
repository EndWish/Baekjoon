#include <iostream>
#include <vector>
#include <stack>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define pii pair<int,int>

int n, m, l, k;
vector<int> xList, yList;
vector<pii> points;

int GetShootingStar(int x, int y, bool sorted);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m >> l >> k;
	points.assign(k, {});
	xList.assign(k, {});
	yList.assign(k, {});
	for (int i = 0; i < k; ++i) {
		cin >> points[i].first >> points[i].second;
		xList[i] = points[i].first;
		yList[i] = points[i].second;
	}

	// 중복값 제거
	ranges::sort(xList);
	xList.erase(ranges::unique(xList).begin(), xList.end());

	ranges::sort(yList);
	yList.erase(ranges::unique(yList).begin(), yList.end());

	// 정답 찾기
	ranges::sort(points);
	int ans = numeric_limits<int>::max();
	for (int x : xList) {
		for (int y : yList) {
			ans = min(ans, GetShootingStar(x, y, true));
		}
	}
	cout << ans;
	
}

int GetShootingStar(int x, int y, bool sorted) {
	int result = points.size();
	if (sorted) {
		int dropNum = ranges::upper_bound(points, x - 1, {}, &pii::first) - points.begin();
		for (auto [px, py] : points | views::drop(dropNum))
			if (x <= px && px <= x + l) {
				if (y <= py && py <= y + l)
					--result;
			}
			else {
				break;
			}	
	}
	else {
		for (auto [px, py] : points)
			if (x <= px && px <= x + l && y <= py && py <= y + l)
				--result;
	}
	return result;
}
