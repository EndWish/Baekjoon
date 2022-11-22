#include <iostream>
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>
#include <cmath>

using namespace std;

int a, b;
vector<int> paliendromes;

array<bool, 10001> sieve;
vector<int> primes;

void SetPaliendromes(int a, int b);
void SetPaliendromesWithDigit(int digit, int pos, int num);

void SetPrimes();
bool IsPrime(int num);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> a >> b;
	SetPaliendromes(a, b);
	SetPrimes();

	//문제해결
	for (int num : paliendromes) {
		if (IsPrime(num))
			cout << num << "\n";
	}

	//출력
	cout << "-1";

}

void SetPaliendromes(int a, int b) {
	int s = log10(a) + 1;
	int e = log10(b) + 1;

	for (int i = s; i <= e; ++i) {
		SetPaliendromesWithDigit(i, 0, 0);
	}
}
void SetPaliendromesWithDigit(int digit, int pos, int num) {
	if ( (digit - 1) / 2 < pos) {
		if (a <= num && num <= b)
			paliendromes.push_back(num);
		return;
	}

	for (int i = 0; i <= 9; ++i) {
		if (pos == 0 && i == 0)
			continue;

		int add = 0;
		add += (int)(pow(10, pos)) * i;
		if(pos * 2 + 1 != digit)
			add += (int)(pow(10, digit - pos - 1)) * i;
		SetPaliendromesWithDigit(digit, pos + 1, num + add);
	}
}
void SetPrimes() {
	sieve.fill(true);
	for (int i = 2; i <= 100; ++i) {
		if (sieve[i]) {	//소수일 경우
			for (int j = i * i; j <= 10000; j += i)
				sieve[j] = false;
			primes.push_back(i);
		}
	}
	for (int i = 101; i <= 10000; ++i) {
		if(sieve[i])
			primes.push_back(i);
	}
}
bool IsPrime(int num) {
	for (int prime : primes) {
		if (num < prime * prime)
			break;
		if (num % prime == 0) {
			return false;
			break;
		}
	}
	return true;
}