#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>

//15711

#define ll long long

using namespace std;

int t;
ll a, b;
vector<ll> primes;

void MakePrimes(vector<ll>& dest);
bool IsPrime(ll num, vector<ll>& predPrimes);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	// 골드바흐의 추측
	// 2초과의 짝수의 경우 두 소수의 합으로 나타낼 수 있다.
	// 홀수의 경우  2+홀수 가 로 나타내는 경우가 아니라면 불가능하다.

	MakePrimes(primes);

	cin >> t;
	while (t-- > 0) {
		//최기화,입력값 받기
		cin >> a >> b;

		//문제해결
		ll len = a + b;

		if (len & 1) {	// 홀수일 경우
			
			ll other = len - 2;
			if(IsPrime(other, primes))
				cout << "YES\n";
			else
				cout << "NO\n";

		}
		else {	// 짝수일 경우
			if (len > 2)
				cout << "YES\n";
			else
				cout << "NO\n";
		}

		//출력
	}

}

void MakePrimes(vector<ll>& dest) 
{
	// 에라토스 테네스의 채로 걸러내기
	const size_t capacity = 2'000'000;
	vector<bool> sieve(capacity + 1, true);
	for (int i = 2; i * i <= capacity; ++i) {
		if (sieve[i])	// 소수를 발견하면
			for (int j = i * i; j <= capacity; j += i)	// 소수의 배수들은 모두 소수가 아니다.
				sieve[j] = false;
	}

	// capacity 까지의 소수들을 저장하기
	dest.clear();
	dest.reserve(capacity / 10);
	for (int i = 2; i <= capacity; ++i)
		if (sieve[i])
			dest.push_back(i);
}

bool IsPrime(ll num, vector<ll>& predPrimes ) {
	if (num <= 1)
		return false;

	auto predRange = [num](ll x) {return x * x <= num; };

	for (ll prime : predPrimes	| views::filter(predRange)) {
		if (num % prime == 0)
			return false;
	}
	return true;
}
