#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <cmath>

#define ll long long
#define pll pair<ll,ll>

using namespace std;

int n;
vector<pll> points;
vector<pll> border;

bool Comp(pll a, pll b);
ll CCW(pll a, pll b, pll c);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	points.assign(n, {});
	border.reserve(n / 3);

	int startIndex = 0;
	for (int i = 0; i < n; ++i) {
		cin >> points[i].first >> points[i].second;
		if (points[i] < points[startIndex]) {
			startIndex = i;
		}
	}

	//문제해결
	swap(points[0], points[startIndex]);
	ranges::sort(points.begin() + 1, points.end(), Comp);

	border.push_back(points[0]);
	border.push_back(points[1]);
	for (int i = 2; i < points.size(); ++i) {
		while (border.size() >= 2) {
			pll a = *(border.rbegin() + 1);
			pll b = *border.rbegin();
			pll c = points[i];

			if (CCW(a, b, c) <= 0) {	// 반시계 방향이 아닐 경우
				border.pop_back();
			}
			else {
				break;
			}
		}
		border.push_back(points[i]);
	}

	//출력
	cout << border.size();
	
}

bool Comp(pll a, pll b) {
	ll ccw = CCW(points[0], a, b);
	if (ccw != 0) {	//일직선상에 없을 경우
		return ccw > 0;
	}
	return a < b;	// points[0]는 가장 왼쪽점중에 가장 아래 있는 점이기 때문에 return a < b는 (일직선상의 두점 중에) points[0]과 더 가까운점을 의미한다.
}

ll CCW(pll a, pll b, pll c) {
	ll x1 = b.first - a.first;
	ll y1 = b.second - a.second;
	ll x2 = c.first - b.first;
	ll y2 = c.second - b.second;

	return x1 * y2 - y1 * x2;
}