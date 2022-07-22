#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

#define DIV 1'000'000'007
#define ll long long

using namespace std;

int n;
vector<int> foods;
vector<ll> dp;

ll MyPow(ll a, ll b);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);	

	// F(i) = i번째 음식이 추가됬을때 추가되는 주헌고통지수의 합
	// x = foods[i] - foods[i-1] : i번째와 i - 1번째 음식의 스코빌 지수의 차
	// F(i) = x + 2 * { F(i - 1) + x * (2^(i-1) - 1) }
	// 식을 풀어보면 F(i) = 2 * F(i - 1) + x * (2^i - 1)

	//최기화,입력값 받기
	cin >> n;
	foods.assign(n, 0);
	dp.assign(n, 0);

	for (int& food : foods) {
		cin >> food;
	}
	ranges::sort(foods);

	//문제해결
	ll ans = 0;
	//dp[0] = 0;	// 0으로 초기화 해놓았기 때문에 할 필요가 없다.
	for (int i = 1; i < n; ++i) {
		ll x = foods[i] - foods[i - 1];
		dp[i] = (2 * dp[i - 1] + x * (MyPow(2, i) - 1)) % DIV;	// (MyPow(2, i) - 1 가 음수가 될 일은 없다. MyPow에서 2의 배수가 10억7로 나누어 떨어지지 않기 때문 
		ans += dp[i];
	}
	ans %= DIV;

	//출력
	cout << ans;
	
}

ll MyPow(ll a, ll b) {
	a %= DIV;

	if (b == 0)
		return 1;
	if (b == 1)
		return a;

	if (b & 1) {	// 홀수일 경우
		return (MyPow(a * a, b / 2) * a) % DIV;
	}
	else {	// 짝수일 경우
		return MyPow(a * a, b / 2);
	}
}
