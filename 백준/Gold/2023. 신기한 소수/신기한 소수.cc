#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>
#include <array>

using namespace std;

int n;
vector<int> primes;
vector<int> ans;

void SetPrimes();
bool IsPrime(int num);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	SetPrimes();
	cin >> n;
	
	//문제해결
	ans.push_back(0);
	for (int i = 0; i < n; ++i) {
		vector<int> nextAns;
		nextAns.reserve(ans.size() * 9);

		for (int num : ans) {
			for (int j = 0; j < 10; ++j) {
				int nextNum = num * 10 + j;
				if (IsPrime(nextNum)) {
					nextAns.push_back(nextNum);
				}
			}
		}

		ans = move(nextAns);
	}

	//출력
	for (auto num : ans)
		cout << num << "\n";

}

void SetPrimes() {
	array<bool, 10000> sieve;
	sieve.fill(true);
	for (int i = 2; i < 100; ++i) {
		if (sieve[i]) {	// 소수일 경우
			for (int j = i * i; j < 10000; j += i) {
				sieve[j] = false;
			}
		}
	}

	for (int i = 2; i < 10000; ++i) {
		if (sieve[i])
			primes.push_back(i);
	}
}

bool IsPrime(int num) {
	if (num == 0 || num == 1)
		return false;

	for (int prime : primes) {
		if (prime * prime > num)
			return true;
		if (num % prime == 0)
			return false;
	}
	return true;
}
