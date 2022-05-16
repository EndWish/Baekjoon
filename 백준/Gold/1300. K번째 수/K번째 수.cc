#include <iostream>
#include <algorithm>

#define ll long long

using namespace std;

 ll n, k;

 ll GetTh(ll num);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> k;

	//문제해결
	ll s = 1, e = n * n;
	while (s < e) {
		ll mid = (s + e) / 2;
		if (k <= GetTh(mid)) {
			e = mid;
		}
		else {
			s = mid + 1;
		}

	}
	
	//출력
	cout << s;
}

ll GetTh(ll num) {
	ll th = 0;
	for (int i = 1; i <= n && i <= num; ++i) {
		th += min(n, num / i);
	}
	return th;
}
