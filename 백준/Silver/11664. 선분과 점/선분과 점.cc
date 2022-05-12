#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

class Point {
public:
	double x, y, z;

	Point() {}
	Point(double x, double y, double z) : x{ x }, y{ y }, z{ z } {
	}

	friend istream& operator>>(istream& is, Point& a) {
		is >> a.x >> a.y >> a.z;
		return is;
	}

	double GetDistance(const Point& rhs) const {
		return sqrt((x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y) + (z - rhs.z) * (z - rhs.z));
	}

};

Point a, b, c;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> a >> b >> c;

	//문제해결
	double aDis, bDis;
	aDis = a.GetDistance(c);
	bDis = b.GetDistance(c);
	while (true) {
		Point mid((a.x + b.x) / 2.0, (a.y + b.y) / 2.0, (a.z + b.z) / 2.0);
		double midDis = mid.GetDistance(c);

		if (aDis - midDis < 0.0000001 && bDis - midDis < 0.0000001) {
			break;
		}

		if (aDis < bDis) {
			bDis = midDis;
			b = mid;
		}
		else {
			aDis = midDis;
			a = mid;
		}

	}

	//출력
	cout.precision(7);
	cout << fixed << aDis;

}


