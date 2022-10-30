#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>
#include <cmath>

using namespace std;

#define ll long long
#define pll pair<ll,ll>

array<pll, 3> points;

long double Distance(pll p1, pll p2);
long double Perimeter(pll p1, pll p2, pll p3);
bool IsLine(pll p1, pll p2, pll p3);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	for (auto& [x, y] : points)
		cin >> x >> y;

	//문제해결
	if (IsLine(points[0], points[1], points[2])) {
		cout << -1;
		return 0;
	}

	long double distMax = -numeric_limits<long double>::max();
	long double distMin = numeric_limits<long double>::max();
	ranges::sort(points);
	do {
		long double perimeter = Perimeter(points[0], points[1], points[2]);
		//cout << "perimeter : " << perimeter << "\n";
		distMax = max(distMax, perimeter);
		distMin = min(distMin, perimeter);
		//cout << "distMax : " << distMax << ", distMin : " << distMin << "\n";
	} while (ranges::next_permutation(points).found);

	//출력
	cout.precision(13);
	cout << fixed << distMax - distMin;

}

long double Distance(pll p1, pll p2) {
	ll dx = p1.first - p2.first;
	ll dy = p1.second - p2.second;
	return sqrtl( dx* dx + dy * dy);
}

long double Perimeter(pll p1, pll p2, pll p3) {
	return 2.L * (Distance(p1, p2) + Distance(p2, p3));
}

bool IsLine(pll p1, pll p2, pll p3) {
	pll v1 = { p1.first - p2.first, p1.second - p2.second };
	pll v2 = { p3.first - p2.first, p3.second - p2.second };
	if (v1.first * v2.second - v2.first * v1.second == 0)
		return true;
	return false;
}
