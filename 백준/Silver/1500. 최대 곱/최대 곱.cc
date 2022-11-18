#include <iostream>
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define ll long long

ll s, k;
ll ans = 1;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> s >> k;
	
	//문제해결
	ll num = s / k;
	ll upper = s % k;
	for (ll i = 0; i < k; ++i) {
		if (i < upper) {
			ans *= (num + 1);
		}
		else {
			ans *= num;
		}
	}

	//출력
	cout << ans;
}