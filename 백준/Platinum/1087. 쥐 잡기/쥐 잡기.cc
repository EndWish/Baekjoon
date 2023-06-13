#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <cmath>

using namespace std;

#define pdd pair<double,double>

pdd operator+(const pdd& a, const pdd& b) {
	return { a.first + b.first, a.second + b.second };
}
pdd operator*(const pdd& a, double d) {
	return { a.first * d, a.second * d };
}

int n;
vector<pdd> poses, velocities;

double Leng(double t);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	poses.assign(n, {});
	velocities.assign(n, {});
	for (int i = 0; i < n; ++i) {
		cin >> poses[i].first >> poses[i].second;
		cin >> velocities[i].first >> velocities[i].second;
	}

	double t0 = 0.0, t1 = 2000.0;
	for (int i = 0; i < 100; ++i) {
		double p = t0 + (t1 - t0) / 3.0;		// 왼쪽 
		double q = t0 + (t1 - t0) * (2.0 / 3.0);	// 오른쪽

		double pLeng = Leng(p);
		double qLeng = Leng(q);

		if (pLeng < qLeng) {
			t1 = q;
		}
		else {
			t0 = p;
		}
	}

	cout.precision(11);
	cout << fixed << Leng(t0);

}

double Leng(double t) {
	pdd low, high;
	low = poses[0] + velocities[0] * t;
	high = poses[0] + velocities[0] * t;

	for (int i = 1; i < n; ++i) {
		pdd curPos = poses[i] + velocities[i] * t;
		low.first = min(low.first, curPos.first);
		low.second = min(low.second, curPos.second);
		high.first = max(high.first, curPos.first);
		high.second = max(high.second, curPos.second);
	}

	return max(high.first - low.first, high.second - low.second);
}
