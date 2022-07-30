#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>

#define pdd pair<double, double>

using namespace std;

int n;
vector<pdd> points;

double Distance2(pdd p1, pdd p2);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;
	points.assign(n, { 0.0,0.0 });
	for (auto& [x, y] : points)
		cin >> x >> y;

	//문제해결
	double minDistance = numeric_limits<double>::max();
	int index = -1;
	for (int i = 0; i < n; ++i) {

		auto p = ranges::max_element(points, [i](pdd a, pdd b) {
			return Distance2(points[i], a) < Distance2(points[i], b);
			});

		double distance = Distance2(points[i], *p) / 2.0;

		if (distance < minDistance) {
			minDistance = distance;
			index = i;
		}
	}

	//출력
	cout << fixed;
	cout.precision(8);
	cout << points[index].first << " " << points[index].second;
	//cout << " : " << minDistance;
	
}

double Distance2(pdd p1, pdd p2) {
	auto [x1, y1] = p1;
	auto [x2, y2] = p2;

	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}
