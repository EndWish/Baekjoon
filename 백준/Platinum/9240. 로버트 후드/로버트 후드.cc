#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <cmath>

using namespace std;

#define ll long long
#define pll pair<ll,ll>

pll operator-(const pll& a, const pll& b) {
	return make_pair(a.first - b.first, a.second - b.second);
}

int n;

vector<pll> GetConvexHull(vector<pll>& points);
double GetMaxDistance(vector<pll>& convexHull);

ll CCW(const pll& p1, const pll& p2, const pll& p3);
ll CCW(const pll& vec1, const pll& vec2);
double GetDistance(const pll& a, const pll& b);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	vector<pll> points(n, { 0,0 });
	for (auto& [x, y] : points)
		cin >> x >> y;
	
	points = GetConvexHull(points);

	double ans = 0;
	if (points.size() == 2) {
		ans = GetDistance(points[0], points[1]);
	}
	else {
		ans = GetMaxDistance(points);
	}
	cout.precision(8);
	cout << fixed << ans;
}

vector<pll> GetConvexHull(vector<pll>& points) {
	// 가장 왼쪽아래점을 인덱스 0번으로 이동시킨다.
	swap(*points.begin(), *ranges::min_element(points));

	// CCW기준으로 정렬시킨다.
	auto pred = [points](const pll& b, const pll& c) {
		pll a = points[0];
		ll ccw = CCW(a, b, c);
		if (ccw == 0)
			return b < c;
		return 0 < ccw;
	};
	ranges::sort(points.begin() + 1, points.end(), pred);

	// 컨벡스헐을 찾는다.
	// 계산의 편의를 위해 points의 첫번째 원소를 마지막에도 넣어준다.
	points.push_back(points[0]);

	vector<pll> result;
	result.push_back(points[0]);
	result.push_back(points[1]);
	for (int i = 2; i < points.size(); ++i) {
		pll p1 = *(result.rbegin() + 1);
		pll p2 = *result.rbegin();
		pll p3 = points[i];

		while (true) {
			ll ccw = CCW(p1, p2, p3);
			if (ccw < 0) {
				result.pop_back();
				p1 = *(result.rbegin() + 1);
				p2 = *result.rbegin();
			}
			else {
				if (ccw == 0) {	// 일직선 상에 있을 경우
					result.pop_back();
				}
				break;
			}
		}
		result.push_back(p3);
	}

	result.pop_back();
	points.pop_back();

	if (result.size() == 1) {
		result.push_back(*points.rbegin());
	}

	return result;
}
double GetMaxDistance(vector<pll>& convexHull) {
	double ans = 0;

	int aIndex = 0, bIndex = 1, cIndex = 1, dIndex = 2;
	pll a = convexHull[aIndex];
	pll b = convexHull[bIndex];
	pll c = convexHull[cIndex];
	pll d = convexHull[dIndex];
	while (true) {
		ans = max(ans, GetDistance(a, c));

		if (0 <= CCW(b - a, d - c)) {
			cIndex = (cIndex + 1) % convexHull.size();
			dIndex = (dIndex + 1) % convexHull.size();
			c = convexHull[cIndex];
			d = convexHull[dIndex];
		}
		else {
			aIndex = aIndex + 1;
			bIndex = (bIndex + 1) % convexHull.size();
			if (aIndex == convexHull.size())
				break;
			a = convexHull[aIndex];
			b = convexHull[bIndex];
		}
	}

	return ans;
}

ll CCW(const pll& p1, const pll& p2, const pll& p3) {
	return CCW(p2 - p1, p3 - p2);
}
ll CCW(const pll& vec1, const pll& vec2) {
	return vec1.first* vec2.second - vec1.second * vec2.first;
}
double GetDistance(const pll& a, const pll& b) {
	double dx = a.first - b.first;
	double dy = a.second - b.second;
	return sqrt(dx * dx + dy * dy);
}