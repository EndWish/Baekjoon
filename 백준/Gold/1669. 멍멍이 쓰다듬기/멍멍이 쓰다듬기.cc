#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define ll long long

ll x, y;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> x >> y;

	//문제해결
	ll diff = y - x;
	ll s = 0, e = 1'000'000'000;
	while (s < e) {
		ll day = (e + s) / 2;
		ll halfDay = (day + 1) / 2;	// 올림

		ll height;		//  day동안 클수있는 최대 키
		if (day & 1) {	// 홀수일 경우
			height = halfDay * halfDay;
		}
		else {	// 짝수일 경우
			height = (halfDay + 1) * halfDay;
		}

		if (diff <= height) {
			e = day;
		}
		else {
			s = day + 1;
		}
	}

	//출력
	cout << s;

}
