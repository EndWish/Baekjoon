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

unordered_map<int, int> Factorizations(int num);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

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
	for (int i = 2; 1 < num; ) {
		if (num % i == 0) {
			++result[i];
			num /= i;
		}
		else {
			++i;
		}
	}
	return result;
}