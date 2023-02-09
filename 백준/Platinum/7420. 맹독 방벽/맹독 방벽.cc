#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <numbers>
#include <cmath>

using namespace std;

#define pii pair<int, int> 

int n, l;
vector<pii> points;
vector<pii> convexhulls;

int CCW(const pii& a, const pii& b, const pii& c);
double Dist(const pii& a, const pii& b);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	//초기화,입력값 받기
	cin >> n >> l;
	points.assign(n, {});
	for (auto& [x, y] : points)
		cin >> x >> y;



	//문제해결
	// 정령한다.
	auto iterMinPoint = ranges::min_element(points);
	swap(*iterMinPoint, *points.begin());
	auto func = [](const pii& a, const pii& b) {
		int ccw = CCW(points[0], a, b);
		//cout << a.first << "," << a.second << " " << b.first << "," << b.second << " : " << ccw << "\n";
		if (ccw == 0) {
			if (a.first == b.first)
				return a.second > b.second;
			return a.first > b.first;
		}	
		return 0 < ccw;
	};
	ranges::sort(points.begin() + 1, points.end(), func);
	points.push_back(points[0]);	// 마지막에 첫번째 원소를 추가한다.

	//cout << "포인트 출력 : \n";
	//for (auto [x, y] : points)
	//	cout << x << " " << y << "\n";

	// 컨벡스헐을 만든다.
	convexhulls.push_back(points[0]);
	convexhulls.push_back(points[1]);
	for (int i = 2; i < points.size(); ++i) {
		pii a = convexhulls[convexhulls.size() - 2];
		pii b = convexhulls[convexhulls.size() - 1];
		pii c = points[i];

		while (CCW(a, b, c) < 0) {
			convexhulls.pop_back();
			a = convexhulls[convexhulls.size() - 2];
			b = convexhulls[convexhulls.size() - 1];

			if (convexhulls.size() <= 1)
				break;
		}
		convexhulls.push_back(c);
	}
	// convexhulls 의 시작점과 끝점이 같다.
	//cout << "컨벡스 헐 출력 : \n";
	//for (auto [x, y] : convexhulls)
	//	cout << x << " " << y << "\n";
		 
	// 길이를 측정한다.
	double ans =  l * 2 * std::numbers::pi;
	for (int i = 0; i < convexhulls.size() - 1; ++i) {
		ans += Dist(convexhulls[i], convexhulls[i + 1]);
	}
	int intAns = round(ans);
	cout << intAns;
}

int CCW(const pii& a, const pii& b, const pii& c) {
	// 두벡터를 구한다.
	pii ab = { b.first - a.first, b.second - a.second };
	pii ac = { c.first - a.first, c.second - a.second };

	// 두벡터를 외적한다.
	return ab.first * ac.second - ab.second * ac.first;
}

double Dist(const pii& a, const pii& b) {
	double dx = a.first - b.first;
	double dy = a.second - b.second;
	return sqrt(dx * dx + dy * dy);
}
