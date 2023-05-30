#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
//#include <format>

using namespace std;

#define INF 40000000

int n, m;
vector<int> nums;
array<array<array<int, 2>, 101>, 51> dp; // dp[구간의 개수][0부터 본 수의 개수][마지막 수를 구간에 포함했는지 여부]
array<array<array<bool, 2>, 101>, 51> visit; // dp[구간의 개수][0부터 본 수의 개수][마지막 수를 구간에 포함했는지 여부]

int DP(int nArea, int len, int have);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	nums.assign(n, {});
	for (int& num : nums)
		cin >> num;

	cout << max(DP(m, n, 0), DP(m, n, 1));
	
}

int DP(int nArea, int len, int have) {
	// 이미 방문을 했다면
	if (visit[nArea][len][have])
		return dp[nArea][len][have];

	visit[nArea][len][have] = true;

	// 아무 구간도 만들지 않은 경우
	if (nArea == 0 && have == 0) {
		dp[nArea][len][have] = 0;
		return dp[nArea][len][have];
	}
	// 불가능한 경우
	else if (len < nArea * 2 - 1) {
		dp[nArea][len][have] = -INF;
		return dp[nArea][len][have];
	}


	// 1.새로운 숫자를 선택하지 않는 경우
	if (have == 0) {
		dp[nArea][len][have] = max(DP(nArea, len - 1, 0), DP(nArea, len - 1, 1));
	}
	// 2.새로운 숫자를 구간에 포함하는 경우
	else {
		dp[nArea][len][have] = max(DP(nArea, len - 1, 1) + nums[len - 1], DP(nArea - 1, len - 1, 0) + nums[len - 1]);
	}
	//cout << format("dp[{}][{}][{}] = {}\n", nArea, len, have, dp[nArea][len][have]);
	return dp[nArea][len][have];
}
