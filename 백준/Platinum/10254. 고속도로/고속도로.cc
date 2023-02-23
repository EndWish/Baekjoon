#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <cmath>

using namespace std;

#define ll long long

struct Point {
	ll x, y;
	
	Point() {
		x = 0; y = 0;
	}
	Point(ll _x, ll _y) {
		x = _x;
		y = _y;
	}


	bool operator<(const Point& other) const {
		return x == other.x ? y < other.y : x < other.x;
	}
	Point operator-(const Point& other) const {
		return Point(x - other.x, y - other.y);
	}

	static ll Distance2(const Point& a, const Point& b) {
		ll dx = a.x - b.x;
		ll dy = a.y - b.y;
		return dx * dx + dy * dy;
	}
	static ll CCW(const Point& a, const Point& b) {
		return a.x * b.y - a.y * b.x;
	}

	friend ostream& operator<<(ostream& os, const Point& point) {
		//return os << "(" << point.x << ", " << point.y << ")";
		return os << point.x << " " << point.y;
 	}
};

int t, n;
vector<Point> points;

vector<Point> ConvexHull();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> t;
	while (t-- > 0) {
		//초기화,입력값 받기
		cin >> n;
		points.assign(n, {});
		for (auto& [x, y] : points)
			cin >> x >> y;

		//문제해결
		// 1. 컨벡스 헐 정점들을 얻는다.
		vector<Point> convexHull = ConvexHull();
		convexHull.push_back(convexHull[0]);

		int ai = 0, bi = 1, ci = 1, di = 2;
		ll maxDist2 = 0;
		pair<Point, Point> ans;
		while (ai != convexHull.size() - 1) {
			Point a = convexHull[ai];
			Point b = convexHull[bi];
			Point c = convexHull[ci];
			Point d = convexHull[di];

			// 두 점의 거리가 더 멀면 갱신해준다.
			ll dist2 = Point::Distance2(a, c);
			if (maxDist2 < dist2) {
				maxDist2 = dist2;
				ans = { a, c };
			}

			//ab 와 cd가 CCW일 경우 cd를 전진시키고 아닐경우 ab를 전진 시킨다.
			if (Point::CCW(b - a, d - c) >= 0) {
				ci = (ci + 1) % convexHull.size();
				di = (di + 1) % convexHull.size();
				if (ci == ai)	// convexHull일 일직선일 경우 무한루프에서 빠져나오게 해준다.
					break;
			}
			else {
				++ai;
				++bi;
			}

		}

		cout << ans.first << " " << ans.second << "\n";

	}
	


}

vector<Point> ConvexHull() {
	// 1. 가장왼쪽 아래에 있는 점을 0번 인덱스로 이동한다.
	auto it = ranges::min_element(points, less<Point>{});
	swap(*it, *points.begin());

	// 2. 0번인덱스를 기준으로 반시계 방향으로 정렬한다.
	auto func = [](const Point& b, const Point& c) {
		Point& a = points[0];
		ll ccw = Point::CCW(b - a, c - a);
		if (ccw == 0)
			return b < c;
		return ccw > 0;
	};
	ranges::sort(points.begin() + 1, points.end(), func);

	// 3. 마지막 원소에 시작원소를 추가한다.
	points.push_back(points[0]);

	// 4. 컨벡스헐 정점들을 구한다.
	vector<Point> convexHull;
	convexHull.reserve(points.size() / 2);

	convexHull.push_back(points[0]);
	convexHull.push_back(points[1]);
	for (Point c : points | views::drop(2)) {
		Point a = *(convexHull.rbegin() + 1);
		Point b = *convexHull.rbegin();

		while (Point::CCW(b - a, c - b) < 0) {
			convexHull.pop_back();
			a = *(convexHull.rbegin() + 1);
			b = *convexHull.rbegin();
		}
		convexHull.push_back(c);
	}
	convexHull.pop_back();

	return convexHull;
}
