#include <iostream>
#include <unordered_set>
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define MAXN 1'299'710

int n;
array<bool, MAXN> sieve;
vector<int> primes;

int SequenceWithPrimes(int num);
void MakePrimes();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	MakePrimes();
	cin >> n;

	//문제해결
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		cout << SequenceWithPrimes(input) << "\n";
	}

	//출력

}

void MakePrimes() {
	sieve.fill(true);
	for (int i = 2; i * i < MAXN; ++i) {
		if (sieve[i]) {	//소수일 경우
			for (int j = i * i; j < MAXN; j += i) {
				sieve[j] = false;
			}
		}
	}

	for (int i = 2; i < MAXN; ++i) {
		if (sieve[i]) {	//소수일 경우
			primes.push_back(i);
		}
	}

}

int SequenceWithPrimes(int num) {
	if (num <= 1)	// 예외 처리
		return 0;

	auto p = ranges::lower_bound(primes, num);
	if (*p == num) {	//소수일 경우 0리턴
		return 0;
	}

	return *p - *(p - 1);
}
