#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <cmath>
#include <iomanip>

using namespace std;

array<int,7> primes = { 2,3,5,7,11,13,17 };
array<array<int, 19>, 19> dp;
double percent;
double chance[2];

int Combi(int n, int k);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	fill_n(&dp[0][0], 19 * 19, -1);

	for (int i = 0; i < 2; ++i) {
		chance[i] = 0;
		cin >> percent;
		percent /= 100.0;

		for (int prime : primes) {
			double subChance = (double)(Combi(18, prime)) * pow(percent, prime) * pow(1.0 - percent, 18 - prime);
			chance[i] += subChance;
		}
	}
	
	double ans = 1.0 - (1.0 - chance[0]) * (1.0 - chance[1]);
	cout.precision(10);
	cout << fixed << ans;

}

int Combi(int n, int k) {
	if (dp[n][k] != -1)
		return dp[n][k];

	if (k == 0 || k == n) {
		return dp[n][k] = 1;
	}

	dp[n][k] = Combi(n - 1, k - 1) + Combi(n - 1, k);
	return dp[n][k];
}
