#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n, f;
array<array<array<int, 10>, 10>, 10> dp; // dp[depth][index] = 결과
array<array<bool, 10>, 10> visit; // dp[depth][index] = 결과


void setDP(int depth, int index);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> f;
	setDP(n - 1, 0);

	vector<int> nums(n);
	iota(nums.begin(), nums.end(), 1);

	do {
		int sum = inner_product(nums.begin(), nums.end(), dp[n - 1][0].begin(), 0);
		if (sum == f)
			break;
	} while (ranges::next_permutation(nums).found);

	for (int num : nums)
		cout << num << " ";

}

void setDP(int depth, int index) {
	if (visit[depth][index]) {
		return;
	}
	visit[depth][index] = true;

	if (depth == 0) {
		dp[depth][index][index] = 1;
		return;
	}

	setDP(depth - 1, index);
	setDP(depth - 1, index + 1);

	for (int i = 0; i < 10; ++i) {
		dp[depth][index][i] += dp[depth - 1][index][i] + dp[depth - 1][index + 1][i];
	}
}