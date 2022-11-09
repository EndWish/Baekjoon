#include <iostream>
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;
#define ll long long

vector<ll> primes;
ll p, a;

void SetPrimes();
bool IsPrime(ll num);
ll PowerMod(ll x, ll y, ll mod);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	//초기화,
	SetPrimes();

	while (true) {
		//입력값 받기
		cin >> p >> a;
		if (p == 0 && a == 0)
			break;

		//문제해결
		if (!IsPrime(p) && PowerMod(a, p, p) == a % p) {
			cout << "yes\n";
		}
		else {
			cout << "no\n";
		}

		//출력
	}


}

void SetPrimes() {
	primes.clear();
	primes.reserve(5133);

	vector<bool> sieve(50'001, true);
	for (ll i = 2; i <= 50'000; ++i) {
		if (sieve[i]) {	//소수일 경우
			primes.push_back(i);
			for (ll j = i * i; j <= 50'000; j += i) {
				sieve[j] = false;
			}
		}
	}
}
bool IsPrime(ll num) {
	for (ll prime : primes) {
		if (prime * prime <= num && num % prime == 0)
			return false;
	}
	return true;
}
ll PowerMod(ll x, ll y, ll mod) {
	x %= mod;

	if (y == 1)
		return x;
	if (y & 1) {	// 홀수 승 일경우
		return (PowerMod((x * x) % mod, y / 2, mod) * x) % mod;
	}
	else {	// 짝수 승 일 경우
		return  PowerMod((x * x) % mod, y / 2, mod) % mod;
	}
}
