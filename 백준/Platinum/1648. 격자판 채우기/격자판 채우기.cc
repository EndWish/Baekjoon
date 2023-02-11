#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>
#define MOD 9901

using namespace std;

int n, m;
vector<vector<int>> dp;	// dp[a][bit] = a번째 칸부터 bit처럼 재워져 있다.

int DP(int slot, int bit);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	dp.assign(n * m + 1, vector<int>((1 << m), -1));

	//문제해결
	cout << DP(0, 0);

}

int DP(int slot, int bit) {
	if (slot == n * m && bit == 0)
		return 1;
	if (slot >= n * m)
		return 0;
	if (dp[slot][bit] != -1)
		return dp[slot][bit];

	dp[slot][bit] = 0;
	if (bit & 1) {
		dp[slot][bit] = DP(slot + 1, bit >> 1);
	}
	else {
		// 세로로 채우는 경우를 +
		dp[slot][bit] += DP(slot + 1, (bit >> 1) | (1 << (m - 1)));
		if(!(bit & 3) && (slot % m) < m - 1)
			dp[slot][bit] += DP(slot + 2, (bit >> 2));
	}
	dp[slot][bit] %= MOD;
	return dp[slot][bit];
}
