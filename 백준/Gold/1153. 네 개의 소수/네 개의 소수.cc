#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n;
array<bool, 1'000'001> sieve;
vector<int> primes;

void SetPrimes();
pair<int, int> getPair(int num);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	// 골드바흐의 추측 : 2보다 큰 짝수는 2개의 소수의 합으로 나타낼 수 있다.

	cin >> n;
	SetPrimes();

	// 불가능한 경우
	if (n < 8) {
		cout << -1;
	}
	// 홀수일 경우
	else if (n & 1) {
		auto [a, b] = getPair(n - 5);
		cout << 2 << " " << 3 << " " << a << " " << b;
	}
	// 짝수일 경우
	else {
		auto [a, b] = getPair(n - 4);
		cout << 2 << " " << 2 << " " << a << " " << b;
	}
	
}

void SetPrimes() {
	sieve.fill(true);
	primes.reserve(n / 10);
	//sieve[0] = false;
	//sieve[1] = false;

	for (int i = 2; i * i <= n; ++i) {
		if (sieve[i]) {
			for (int j = i * i; j <= n; j += i) {
				sieve[j] = false;
			}
		}
	}

	for (int i = 2; i <= n; ++i) {
		if (sieve[i])
			primes.push_back(i);
	}

}

pair<int, int> getPair(int num) {
	for (int prime : primes) {
		int otherPrime = num - prime;
		if (0 < otherPrime && ranges::binary_search(primes, otherPrime)) {
			return { prime, otherPrime };
		}
	}

	return { -1, -1 };
}
