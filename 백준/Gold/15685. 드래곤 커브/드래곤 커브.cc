#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define pii pair<int,int>
pii operator+(const pii& a, const pii& b);
pii operator-(const pii& a, const pii& b);

array<vector<pii>, 11> dragonCurves;
array<array<bool, 101>, 101> board;

pii TurnCW90(const pii& point);
pii TurnCCW90(const pii& point);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	dragonCurves[0].emplace_back(0, 0);
	dragonCurves[0].emplace_back(1, 0);
	for (int i = 1; i <= 10; ++i) {
		dragonCurves[i] = dragonCurves[i - 1];
		pii endPoint = *dragonCurves[i].rbegin();
		for (int j = dragonCurves[i].size() - 2; 0 <= j; --j) {
			dragonCurves[i].push_back(TurnCW90(dragonCurves[i][j] - endPoint) + endPoint);
		}
	}

	//문제해결
	int n, d, g;
	pii endPoint;
	cin >> n;
	while (n-- > 0) {
		cin >> endPoint.first >> endPoint.second >> d >> g;
		for (auto point : dragonCurves[g]) {
			for (int i = 0; i < d; ++i)
				point = TurnCCW90(point);
			point = point + endPoint;
			board[point.first][point.second] = true;
		}
	}

	int dx[] = { 0, 1, 1, 0 };
	int dy[] = { 0, 0, 1, 1 };
	int ans = 0;
	for (int x = 0; x < 100; ++x) {
		for (int y = 0; y < 100; ++y) {
			bool dragonRect = true;
			for (int i = 0; i < 4; ++i) {
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (!board[nx][ny]) {
					dragonRect = false;
					break;
				}
			}
			if (dragonRect)
				++ans;
		}
	}
	cout << ans;
}

pii operator+(const pii& a, const pii& b) {
	return { a.first + b.first, a.second + b.second };
}
pii operator-(const pii& a, const pii& b) {
	return { a.first - b.first, a.second - b.second };
}

pii TurnCW90(const pii& point) {
	return { -point.second, point.first };
}
pii TurnCCW90(const pii& point) {
	return { point.second, -point.first };
}
