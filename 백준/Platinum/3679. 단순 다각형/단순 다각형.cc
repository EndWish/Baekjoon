#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXN 2000
#define ll long long

using namespace std;

class Point {
public:
	ll x, y, id;

	Point() = default;
	Point(ll _x, ll _y, ll _id = -1) {
		x = _x;
		y = _y;
		id = _id;
	}
	Point operator-(const Point& rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
};

int t;
int n;
vector<Point> points;

ll CCW(const Point& a, const Point& b, const Point& c);

int main() 
{

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	points.reserve(MAXN);

	cin >> t;
	while (t-- > 0) {
		//초기화,입력값 받기
		cin >> n;
		points.assign(n, {});
		for (size_t index = 0; auto & point : points) {
			cin >> point.x >> point.y;
			point.id = index++;
		}

		//문제해결
		// 가장 왼쪽, 그중에서도 가장아래에 있는 점을 0번째 인덱스로 바꾼다.
		auto p = ranges::min_element(points, [](const Point& a, const Point& b) {
			return make_pair(a.x, a.y) < make_pair(b.x, b.y);
			});
		swap(*points.begin(), *p);

		// 0번째 인덱스를 기준으로 반시계 방향으로 정렬한다.
		// 같은 각도일 경우 기준에 더 가까운 점을 먼저 오도록한다.
		ranges::sort(points.begin() + 1, points.end(), [](const Point& a, const Point& b) {
			ll ccw = CCW(points[0], a, b);
			if (ccw != 0LL)
				return ccw > 0LL;
			return make_pair(a.x, a.y) < make_pair(b.x, b.y);
			});

		int lastVertex = n - 1;
		while (lastVertex > 0 && CCW(points[0], points[lastVertex], points[lastVertex - 1]) == 0) {
			--lastVertex;
		}

		//출력
		for (int i = 0; i < lastVertex; ++i) {
			cout << points[i].id << " ";
		}
		for (int i = n - 1; i >= lastVertex; --i) {
			cout << points[i].id << " ";
		}
		cout << "\n";

	}

}

ll CCW(const Point& a, const Point& b, const Point& c) 
{
	Point ab = b - a;
	Point ac = c - a;
	return ab.x * ac.y - ab.y * ac.x;
}
