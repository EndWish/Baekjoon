#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <cmath>

// 1007

using namespace std;

class Position : public pair<int, int> {
public:

	Position() = default;
	Position(int x, int y) : pair<int, int>(x, y) {};

	Position operator*(const int rhs) const {
		return Position(first * rhs, second * rhs);
	}

	Position operator+(const Position& rhs) const {
		return Position(first + rhs.first, second + rhs.second);
	}

	double GetDistance() {
		double x = first;
		double y = second;
		return sqrt(x * x + y * y);
	}

};

int t;
int n;
vector<Position> points;
vector<int> comb;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> t;
	while (t-- > 0) {
		//최기화,입력값 받기
		cin >> n;
		points.resize(n);	// 점들의 값 받아오기
		for (Position& point : points)
			cin >> point.first >> point.second;

		comb.resize(n);	// 콤비네이션 구현
		fill(comb.begin(), comb.begin() + n / 2, 1);
		fill(comb.begin() + n / 2, comb.end(), -1);
		ranges::sort(comb);

		//문제해결
		double ans = numeric_limits<double>::max();
		do {
			// 모든 벡터들의 합구하기
			Position sum = inner_product(points.begin(), points.end(), comb.begin(), Position(0, 0));	// 내적(요소곱들의 합)
			ans = min(ans, sum.GetDistance());
		} while (ranges::next_permutation(comb).found);

		//출력
		cout.precision(10);
		cout << fixed << ans << "\n";

	}


}