#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

int n;
array<long long, 3> dp;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	dp = { 0,1,1 };

	//문제해결
	for (int i = 2; i <= n; ++i) {
		dp[2] = dp[1] + dp[0];
		dp[0] = dp[1];
		dp[1] = dp[2];
	}

	//출력
	cout << dp[1];

}
