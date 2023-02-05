#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define INF numeric_limits<int>::max()

int n;
string s, e;
array<array<int, 10>, 10'001> dp;	// dp[숫자나사][왼쪽으로 돌린 횟수] = 숫자나사 번호까지 맞추는데 회전한 최소값

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	fill_n(&dp[0][0], 10'001 * 10, INF);
	dp[0][0] = 0;

	cin >> n >> s >> e;
	s.insert(s.begin(), 0);
	e.insert(e.begin(), 0);
	ranges::transform(s, s.begin(), [](char ch) {return ch - '0'; });
	ranges::transform(e, e.begin(), [](char ch) {return ch - '0'; });

	//문제해결
	for (int bolt = 0; bolt < n; ++bolt) {
		for (int spin = 0; spin < 10; ++spin) {
			if (dp[bolt][spin] == INF)
				continue;

			// bolt + 1 번째 나사를 돌려보자!
			int num = (s[bolt + 1] + spin) % 10;	// bolt + 1번째 나사의 번호
			int goal = e[bolt + 1];

			// 왼쪽으로 돌리는 경우
			int addTurn = num <= goal ? goal - num : 10 - (num - goal);
			int& dest1 = dp[bolt + 1][(spin + addTurn) % 10];
			dest1 = min(dest1, dp[bolt][spin] + addTurn);

			// 오른쪽으로 돌리는 경우
			addTurn = goal <= num ? num - goal : 10 - (goal - num);
			int& dest2 = dp[bolt + 1][spin];
			dest2 = min(dest2, dp[bolt][spin] + addTurn);

		}
	}
	
	int ans = INF;
	for (int spin = 0; spin < 10; ++spin)
		ans = min(ans, dp[n][spin]);
	cout << ans;

}
