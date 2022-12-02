#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; ++i) {

		int x1, y1, r1, x2, y2, r2;
		cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
		if (r1 < r2) {
			int tempX = x1, tempY = y1, tempR = r1;
			x1 = x2; y1 = y2; r1 = r2;
			x2 = tempX; y2 = tempY; r2 = tempR;
		}

		float dir = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

		if (dir > r1 + r2) {
			cout << 0;
		}
		else if (dir == r1 + r2) {
			cout << 1;
		}
		else if (dir < r1 + r2) {
			if (r1 == dir + r2) {
				if (r1 == r2) {
					cout << -1;
				}
				else {
					cout << 1;
				}
			}
			else if (r1 > dir + r2) {
				cout << 0;
			}
			else {
				cout << 2;
			}
		}

		cout << '\n';
	}

	return 0;
}