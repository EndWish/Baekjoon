#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define MAXN 100'001

int a, b;
array<bool, MAXN> sieve;
vector<int> primes;

void EratosThenes();
bool IsUnderPrime(int num);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	EratosThenes();
	cin >> a >> b;

	//문제해결
	int ans = 0;
	for (int i = a; i <= b; ++i) {
		if (IsUnderPrime(i))
			++ans;
	}

	//출력
	cout << ans;

}

void EratosThenes() {
	sieve.fill(true);

	sieve[0] = false;
	sieve[1] = false;
	for (int i = 2; i * i < MAXN; ++i) {
		if (sieve[i]) {	// 소수일 경우
			
			for (int j = i * i; j < MAXN; j += i) {	// 그 수의 배수는 소수가 아니다.
				sieve[j] = false;
			}
		}
	}

	for (int i = 2; i < MAXN; ++i) {
		if (sieve[i])
			primes.push_back(i);
	}
}

bool IsUnderPrime(int num) {
	int primeFactorNum = 0;

	int index = 0;
	while (num != 1) {
		if (num % primes[index] == 0) {	// index번째 소수로 나누어 질 경우
			++primeFactorNum;
			num /= primes[index];
		}
		else {
			++index;
		}
	}

	return sieve[primeFactorNum];
}
