#include <iostream>

using namespace std;

int n;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;

	//문제해결
	int x;
	while (cin >> x) {
		if (x < 10) {
			cout << x << "\n";
			continue;
		}

		int temp = 10;
		while (x > temp) {
			int under = x % temp;
			int mid = under / (temp / 10);
			if (mid >= 5)	//반올림
				x += - under + temp;
			else
				x -= under;

			temp *= 10;
		}

		cout << x << "\n";

	}

	//출력

}