#include <iostream>
#include <vector>
#include <ranges>
#include <cmath>

#define ll long long

using namespace std;

ll n;

ll phi(ll n);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;

	//문제해결
	cout << phi(n);

	//출력
	
}

ll phi(ll n) {
	if (n == 1)
		return 1;

	ll x = n;
	ll prime = 2;
	vector<pair<ll,ll>> primes;
	while (prime <= (ll)sqrt(x)) {
		if (x % prime == 0) {	// 나누어 떨어질 경우
			x /= prime;

			// 삽입
			if (!primes.empty() && primes.back().first == prime) {
				++primes.back().second;
			}
			else {
				primes.emplace_back(prime, 1);
			}
		}
		else {	// 나누어 떨어지지 않을 경우
			++prime;
		}
	}

	// 삽입
	if (!primes.empty() && primes.back().first == x) {
		++primes.back().second;
	}
	else {
		primes.emplace_back(x, 1);
	}

	ll res = 1;
	for (auto[p, k] : primes) {
		res *= (ll)pow(p, k - 1) * (p - 1);
	}
	return res;

}
