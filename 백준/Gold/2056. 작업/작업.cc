#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define INF numeric_limits<int>::max()

int n;
vector<int> workTimes;
vector<int> dp;
vector<vector<int>> pres;

int DP(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	workTimes.assign(n + 1, {});
	dp.assign(n + 1, {});
	pres.assign(n + 1, {});
	for (int i = 1; i <= n; ++i) {
		cin >> workTimes[i];

		int prevNum;
		cin >> prevNum;
		pres[i].assign(prevNum, {});
		for (int& pre : pres[i]) {
			cin >> pre;
		}
	}

	//문제해결
	int ans = 0;
	for (int node = 1; node <= n; ++node) {
		ans = max(ans, DP(node));
	}

	//출력
	cout << ans;

}

int DP(int node) {
	// 이미 계산을 해놨다면 바로 리턴
	if (dp[node] != 0)
		return dp[node];

	// node를 수행하는데 걸리는 최소시간을 구한다.
	dp[node] = workTimes[node];
	for (int pre : pres[node]) {	// 선행노드의 마감시간을 읽어와서 구해본다.
		dp[node] = max(dp[node], DP(pre) + workTimes[node]);
	}

	return dp[node];
}
