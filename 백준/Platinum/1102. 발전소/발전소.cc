#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <queue>
#include <numeric>
#include <bitset>

using namespace std;

#define MAXN 16

int n, p, sp, ans;
array<array<int, MAXN>, MAXN> costs;
int start;
array<int, 1024 * 64> dp;

int NumOfOne(int x);
int DP(int x);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	ans = numeric_limits<int>::max();
	cin >> n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> costs[i][j];
	for (int i = 0; i < n; ++i) {
		char ch;
		cin >> ch;
		if (ch == 'Y') {
			start += (1 << i);
			++sp;
		}
	}
	cin >> p;
	
	//문제해결
	// 1. 예외 처리
	if (p <= sp) {
		cout << 0;
		return 0;
	}
	else if (n < p || sp == 0) {
		cout << -1;
		return 0;
	}

	// 2. 문제 풀이
	dp.fill(-1);
	dp[start] = 0;
	DP((1 << n) - 1);

	//출력
	cout << ans;

}

int NumOfOne(int x) {
	int count = 0;
	while (x) {
		x &= x - 1;
		++count;
	}
	return count;
}

int DP(int x) {
	if (dp[x] != -1)
		return dp[x];

	dp[x] = numeric_limits<int>::max();
	for (int j = 0; j < n; ++j) {	// 이전 단계에서 새로 고친 발전소 j를 찾는다.
		int bitj = (1 << j);
		if ((bitj & x) == 0 || (bitj & start))
			continue;

		int preX = x - bitj;
		for (int i = 0; i < n; ++i) {	// i로부터 j를 고칠때 발생하는 총비용을 구해 최소값을 찾는다.
			int biti = (1 << i);
			if ((biti & preX) == 0)
				continue;

			dp[x] = min(dp[x], DP(preX) + costs[i][j]);
		}
	}

	//cout << bitset<16>(x) << ":" << dp[x] << "\n";
	if (NumOfOne(x) >= p) {
		ans = min(ans, dp[x]);
	}
	return dp[x];
}
