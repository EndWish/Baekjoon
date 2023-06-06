#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <cmath>

using namespace std;

int n;
vector<int> nums;
vector<unordered_map<int, int>> factors;
unordered_map<int, int> allFactor;
vector<int> primes;

unordered_map<int, int> Factorizations(int num);
vector<int> GetEratosthenesSieve(int num);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	primes = GetEratosthenesSieve(1'000'000);

	cin >> n;
	nums.assign(n, {});
	for (int& num : nums)
		cin >> num;
	
	for (int num : nums) {
		unordered_map<int, int> factor = Factorizations(num);
		for (auto [num, cnt] : factor)
			allFactor[num] += cnt;
		factors.push_back(move(factor));
	}

	int gcd = 1;
	for (auto& [num, cnt] : allFactor) {
		cnt /= n;
		gcd *= pow(num, cnt);
	}

	int moveCount = 0;
	for (unordered_map<int, int>& factor : factors) {
		for (auto [num,cnt] : allFactor) {
			moveCount += max(cnt - factor[num], 0);
		}
	}

	cout << gcd << " " << moveCount;

}

unordered_map<int, int> Factorizations(int num) {
	unordered_map<int, int> result;
	for (int prime : primes) {
		while (num % prime == 0) {
			num /= prime;
			++result[prime];
		}
		if (num == 1)
			break;
	}
	return result;
}

vector<int> GetEratosthenesSieve(int num) {
	vector<int> primes;
	primes.reserve(num / 10);

	vector<bool> check(num + 1, true);
	for (long long i = 2; i * i <= num; ++i) {
		if (check[i]) {
			for (int j = i * i; j <= num; j += i) {
				check[j] = false;
			}
		}
	}

	for (int i = 2; i <= num; ++i) {
		if (check[i]) {
			primes.push_back(i);
		}
	}

	return primes;
}
