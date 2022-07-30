#include <iostream>
#include <vector>
#include <ranges>

#define MAXN 4'000'001
#define MOD 1'000'000'007

#define ll long long

using namespace std;

ll m, n, k;
vector<ll> factorials;

ll myPow(ll a, ll b);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	factorials.assign(MAXN, 0);
	factorials[0] = 1;
	for (int i = 1; i < MAXN; ++i) {
		factorials[i] = (factorials[i - 1] * i) % MOD;
	}

	//문제해결
	cin >> m;
	for (int i = 0; i < m; ++i) {
		cin >> n >> k;

		/*
		nCk = n!/((n-k!)k!) = n! * ((n-k!)k!)^-1
		n! * ((n-k!)k!)^-1 (mod p) = n! * ((n-k!)k!)^(p-2) (mod p)
			왜냐하면 a^p = a (mod p) (p는 소수, a는 p의 배수가 아닐때)
			위 식에서 a^2으로 양변을 나누면 a^(p-2) = a^-1 (mod p) 식을 유도할 수 있다.
		*/

		ll ans = (factorials[n] * myPow((factorials[n - k] * factorials[k]), MOD - 2)) % MOD;
		cout << ans << "\n";
	}

	//출력
	
}

ll myPow(ll a, ll b) 
{
	a %= MOD;
	if (b == 0)
		return 1;
	if (b == 1)
		return a;
	if (b & 1)
		return (myPow(a * a, b / 2) * a) % MOD;	// b가 홀수 일때
	return myPow(a * a, b / 2) % MOD;	// b가 짝수 일때
}
