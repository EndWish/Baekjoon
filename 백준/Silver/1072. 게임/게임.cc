#include <iostream>
#include <numeric>
#define ll long long

using namespace std;

ll x, y;

ll WinnigRate(ll extraWinNum);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> x >> y;

	//문제해결
	ll z = WinnigRate(0);
	if (z == 100 || z == 99) {
		cout << -1;
		return 0;
	}

	ll s = 0, e = x;
	while (s < e) {
		ll mid = (s + e) / 2;
		if (WinnigRate(mid) == z) {
			s = mid + 1;
		}
		else {
			e = mid;
		}
	}

	//출력
	cout << s;

}

ll WinnigRate(ll extraWinNum) {
	return (y + extraWinNum) * 100 / (x + extraWinNum);
}

