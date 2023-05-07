#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long
#define pii pair<ll,ll>

pii operator-(const pii& a, const pii& b) {
	return { a.first - b.first, a.second - b.second };
}

int n;
vector<pii> points;

ll dotProduct(pii a, pii b);
bool isRightTriangle(pii a, pii b, pii c);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	points.assign(n, {});
	for (auto& [x, y] : points)
		cin >> x >> y;

	ll ans = 0;
	for (int i = 0; i < points.size(); ++i) {
		for (int j = i + 1; j < points.size(); ++j) {
			for (int k = j + 1; k < points.size(); ++k) {
				if (isRightTriangle(points[i], points[j], points[k]))
					++ans;
			}
		}
	}
	cout << ans;
	
}

ll dotProduct(pii a, pii b) {
	return a.first * b.first + a.second * b.second;
}

bool isRightTriangle(pii a, pii b, pii c) {
	if (dotProduct(b - a, c - b) == 0LL)	// ab, bc
		return true;
	if (dotProduct(c - b, a - c) == 0LL)	// bc, ca
		return true;
	if (dotProduct(a - c, b - a) == 0LL)	// ca, ab
		return true;
	return false;
}
