#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define MAXN 500

long long n, l, w, h;
long double s, e;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> l >> w >> h;
	s = 0;
	e = 1'000'000'000;

	//문제해결
	while (true) {
		long double mid = (s + e) / 2.0L;

		long long a = l / mid;
		long long b = w / mid;
		long long c = h / mid;
		long long num = a * b;
		if (num <= n || c == 0) {
			num *= c;
		}

		if (num < n) {
			e = mid;
		}
		else {
			s = mid;
		}

		//cout.precision(10);
		//cout << fixed << s << " " << e << "\n";

		if (abs(e - s) < 0.000'000'000'1L) {
			break;
		}
	}

	//출력
	cout.precision(10);
	cout << fixed << s;

}
