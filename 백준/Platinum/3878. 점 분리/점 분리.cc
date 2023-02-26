#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long
#define Point pair<int,int>

Point operator-(const Point& a, const Point& b) {
	return { a.first - b.first, a.second - b.second };
}
ostream& operator<<(ostream& os, const Point& p) {
	return os << "(" << p.first << "," << p.second << ")";
}

int t, n, m;
vector<Point> points1, points2;

int CCW(const Point& v1, const Point& v2);
int CCW(const Point& p1, const Point& p2, const Point& p3);
vector<Point> ConvexHull(vector<Point>& points);

bool Cross(const Point& a, const Point& b, const Point& c, const Point& d);
bool Contain(const Point& a, const Point& b, const Point& p, bool checkZeroCCW = false);
bool Inside(vector<Point>& ccwConvexHull, const Point& p);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


	cin >> t;
	while (t-- > 0) {
		//초기화,입력값 받기
		cin >> n >> m;
		points1.assign(n, {});
		points2.assign(m, {});
		for (auto& [x, y] : points1)
			cin >> x >> y;
		for (auto& [x, y] : points2)
			cin >> x >> y;

		//문제해결

		// 1. 컨벡스 헐을 구한다.
		if (points1.size() < points2.size())
			swap(points1, points2);
		points1 = ConvexHull(points1);
		points2 = ConvexHull(points2);

		// 점이 하나씩만 있을 경우
		if (points1.size() == 1) {
			cout << "YES\n";
			continue;
		}
		// 점과 직선일 경우
		if (points1.size() == 2 && points2.size() == 1) {
			if (Contain(points1[0], points1[1], points2[0]))
				cout << "NO\n";
			else
				cout << "YES\n";
			continue;
		}
		// 직선 2개일 경우
		if (points1.size() == 2 && points2.size() == 2) {
			if (Cross(points1[0], points1[1], points2[0], points2[1]))
				cout << "NO\n";
			else
				cout << "YES\n";
			continue;
		}

		// points1 이 다각형일 경우
		bool inside = false;
		for (auto p : points2) {
			if (Inside(points1, p)) {
				inside = true;
				break;
			}
		}
		// points2가 다각형일 경우
		if (3 <= points2.size() && !inside) {
			for (auto p : points1) {
				if (Inside(points2, p)) {
					inside = true;
					break;
				}
			}
		}

		if (inside)
			cout << "NO\n";
		else
			cout << "YES\n";

	}

}

int CCW(const Point& v1, const Point& v2) {
	return v1.first * v2.second - v1.second * v2.first;
}

int CCW(const Point& p1, const Point& p2, const Point& p3) {
	return CCW(p2 - p1, p3 - p2);
}

vector<Point> ConvexHull(vector<Point>& points) {

	// 1. 가장 왼쪽 아래점을 인덱스0번으로 이동시킨다.
	swap(points[0], *ranges::min_element(points, less<Point>{}));

	// 2. 0번인데스 기준으로 반시계방향으로 정렬시킨다.
	auto func = [points](const Point& b, const Point& c) {
		const Point& a = points[0];
		int ccw = CCW(a, b, c);
		if (ccw == 0) {	// 세점이 일직선 상에 있을 경우
			// 가까운점이 먼저 오도록한다.
			return b < c;
		}
		return 0 < ccw;
	};
	ranges::sort(points.begin() + 1, points.end(), func);

	// 3. 볼록껍질 점들을 찾는다.
	points.push_back(points[0]);	// 계산을 편하게 하기 위해 첫번째 점을 마지막에도 넣는다.
	
	vector<Point> result;
	result.push_back(points[0]);
	result.push_back(points[1]);
	for (int i = 2; i < points.size(); ++i) {
		Point a = *(result.rbegin() + 1);
		Point b = *result.rbegin();
		Point c = points[i];
		while (true) {	// 반시계방향이 아닐경우
			int ccw = CCW(a, b, c);
			if (ccw < 0) {
				result.pop_back();
				a = *(result.rbegin() + 1);
				b = *result.rbegin();
			}
			else {
				if(ccw == 0 && i != points.size() - 1)
					result.pop_back();
				break;
			}
		}
		result.push_back(c);
	}

	points.pop_back();
	result.pop_back();

	return result;
}

bool Cross(const Point& a, const Point& b, const Point& c, const Point& d) {
	// ab선분기준으로 c점과 d점이 한쪽에 있으면 겹치지 않는다.
	ll ccwABC = CCW(a, b, c);
	ll ccwABD = CCW(a, b, d);
	if (0 < ccwABC * ccwABD)
		return false;

	// cd선분기준으로 a점과 b점이 한쪽에 있으면 겹치지 않는다.
	ll ccwCDA = CCW(c, d, a);
	ll ccwCDB = CCW(c, d, b);
	if (0 < ccwCDA * ccwCDB)
		return false;

	// 어느 세점이 일직선 상에 있을때 포함되는지 확인한다.

	if ((ccwABC == 0 && !Contain(a, b, c, true)) &&
		(ccwABD == 0 && !Contain(a, b, d, true)) &&
		(ccwCDA == 0 && !Contain(c, d, a, true)) &&
		(ccwCDB == 0 && !Contain(c, d, b, true)) )
		return false;

	return true;
}

bool Contain(const Point& a, const Point& b, const Point& p, bool checkZeroCCW) {
	// CCW가 0이 아닐경우 포함될 수가 없다.
	if (!checkZeroCCW && CCW(a, b, p) != 0)
		return false;
	// 점p가 x값과 y값 전부 그 사이에 포함된다면 포함되는 것이다.
	if (min(a.first, b.first) <= p.first && p.first <= max(a.first, b.first) &&
		min(a.second, b.second) <= p.second && p.second <= max(a.second, b.second))
		return true;
	return false;
}

bool Inside(vector<Point>& ccwConvexHull, const Point& p) {
	bool inside = true;
	ccwConvexHull.push_back(ccwConvexHull[0]);
	for (int i = 0; i < ccwConvexHull.size() - 1; ++i) {
		Point& a = ccwConvexHull[i];
		Point& b = ccwConvexHull[i + 1];
		int ccw = CCW(a, b, p);
		if (ccw < 0 || (ccw == 0 && !Contain(a, b, p, true))) {
			inside = false;
			break;
		}
	}

	ccwConvexHull.pop_back();
	return inside;
}
