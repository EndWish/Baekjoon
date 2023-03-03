#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <cmath>

using namespace std;

#define ll long long
#define Point pair<ll,ll>
Point operator-(const Point& a, const Point& b);

int n;
vector<Point> points;

ll CCW(const Point& a, const Point& b, const Point& c, const Point& d);
ll CCW(const Point& a, const Point& b, const Point& c);
ll CCW(const Point& a, const Point& b);

vector<Point> ConvexHull(vector<Point>& _points);

double GetMinWidth(vector<Point>& _convex);

double GetDistance(const Point& a, const Point& b, const Point& c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int cnt = 1;
	while(cin >> n) {
		//초기화,입력값 받기
		if (n == 0)
			break;

		points.assign(n, {});
		for (auto& [x, y] : points)
			cin >> x >> y;

		//문제해결
		points = ConvexHull(points);	// 볼록껍질 정점을 얻는다.
		double wid = GetMinWidth(points);
		wid = ceil(wid * 100.) / 100.;
		cout.precision(2);
		cout << fixed << "Case " << cnt++ << ": " << wid << "\n";
	}

	
}

vector<Point> ConvexHull(vector<Point>& _points) {
	// 1. 가장 왼쪽 아래에 있는 점을 찾아 인덱스 0번과 바꾼다.
	swap(_points[0], *ranges::min_element(_points));

	// 2. 반시계 방향으로 정렬시킨다.
	auto pred = [](const Point& b, const Point& c) {
		Point& a = points[0];
		ll ccw = CCW(a, b, c);
		if (ccw == 0)
			return b < c;
		else
			return 0 < ccw;
	};
	ranges::sort(_points.begin() + 1, _points.end(), pred);

	// 3. 컨벡스헐을 찾는다.
	_points.push_back(_points[0]);

	vector<Point> convex;
	convex.push_back(_points[0]);
	convex.push_back(_points[1]);
	for (int i = 2; i < _points.size(); ++i) {
		Point a = *(convex.rbegin() + 1);
		Point b = *convex.rbegin();
		Point c = _points[i];

		
		while (true) {
			ll ccw = CCW(a, b, c);
			if (ccw == 0) {	// 직선상에 있을 경우
				convex.pop_back();
				break;
			}
			else if (ccw < 0) {	// 시계방향으로 꺽일 경우
				convex.pop_back();
				a = *(convex.rbegin() + 1);
				b = *convex.rbegin();
			}
			else {	// 반시계 방향일 경우
				break;
			}
		}

		convex.push_back(c);
	}

	_points.pop_back();
	convex.pop_back();
	return convex;
}

double GetMinWidth(vector<Point>& _convex) {
	double ans = numeric_limits<double>::max();

	points.push_back(points[0]);	// 계산의 편의를 위해 첫번째 정점을 마지막에도 추가한다.

	int aIndex = 0;
	int cIndex = 1;
	Point a = _convex[aIndex];
	Point b = _convex[aIndex + 1];
	Point c = _convex[cIndex];
	Point d = _convex[(cIndex + 1) % points.size()];
	while (aIndex != points.size() - 1) {
		// 직선 ab와 가장 멀리 있는 점 c를 찾아낸다.
		ll ccw = CCW(a, b, c, d);
		while (0 < ccw) {	// ab선분과 cd선분이 반시계 방향일경우 선분cd를 전진시킨다.
			cIndex = (cIndex + 1) % (points.size() - 1);	// 마지막에 첫번째 정점을 넣어줬으므로 스킵하기위해 (points.size() - 1) 로 나머지연산을 한다.

			c = _convex[cIndex];
			d = _convex[(cIndex + 1) % points.size()];
			ccw = CCW(a, b, c, d);
		}

		// 직선 ab와 점 c의 거리를 얻는다.
		ans = min(ans, GetDistance(a, b, c));
		
		// 직선 ab를 전진시킨다.
		aIndex = (aIndex + 1) % points.size();
		a = _convex[aIndex];
		b = _convex[(aIndex + 1) % points.size()];
	}
	return ans;
}

ll Dot(const Point& vec1, const Point& vec2) {
	return vec1.first * vec2.first + vec1.second + vec2.second;
}

double GetDistance(const Point& p1, const Point& p2, const Point& p3) {
	// ax + by + c = 0
	// a = -dy, b = dx, c = x1*y2 - x2*y1 (=Cross(p1,p2))
	// abs(ax + by + c) / sqrt(a*a + b * b)
	double a = -(p2.second - p1.second);
	double b = p2.first - p1.first;
	double c = p1.first * p2.second - p2.first * p1.second;
	double x = p3.first;
	double y = p3.second;
	return abs(a * x + b * y + c) / sqrt(a * a + b * b);
}

Point operator-(const Point& a, const Point& b) {
	return { a.first - b.first, a.second - b.second };
}

ll CCW(const Point& a, const Point& b, const Point& c, const Point& d) {
	return CCW(b - a, d - c);
}

ll CCW(const Point& a, const Point& b, const Point& c) {
	return CCW(b - a, c - b);
}

ll CCW(const Point& a, const Point& b) {
	return a.first * b.second - b.first * a.second;
}
