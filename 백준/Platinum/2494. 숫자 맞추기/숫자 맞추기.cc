#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define INF numeric_limits<int>::max()
#define pii pair<int,int>

int n;
string s, e;
array<array<int, 10>, 10'001> dp;
array<array<pii, 10>, 10'001> path;
array<array<int, 10>, 10'001> ansSpin;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	fill_n(&dp[0][0], 10 * 10'001, INF);
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

			int num = (s[bolt + 1] + spin) % 10;
			int goal = e[bolt + 1];

			// 왼쪽으로 돌리는 경우
			int addTurn = num <= goal ? goal - num : 10 - (num - goal);
			int& dest1 = dp[bolt + 1][(spin + addTurn) % 10];
			if (dp[bolt][spin] + addTurn < dest1) {
				dest1 = dp[bolt][spin] + addTurn;
				path[bolt + 1][(spin + addTurn) % 10] = { bolt, spin };
				ansSpin[bolt + 1][(spin + addTurn) % 10] = addTurn;
			}

			//오른쪽으로 돌리는 경우
			addTurn = goal <= num ? num - goal : 10 - (goal - num);
			int& dest2 = dp[bolt + 1][spin];
			if (dp[bolt][spin] + addTurn < dest2) {
				dest2 = dp[bolt][spin] + addTurn;
				path[bolt + 1][spin] = { bolt, spin };
				ansSpin[bolt + 1][spin] = -addTurn;
			}
		}
	}

	int ans = INF;
	pii pos;
	for (int spin = 0; spin < 10; ++spin) {
		if (dp[n][spin] < ans) {
			ans = dp[n][spin];
			pos = { n, spin };
		}
	}
	cout << ans << "\n";
	vector<pii> anses;
	while (0 < pos.first) {
		anses.emplace_back(pos.first, ansSpin[pos.first][pos.second]);
		pos = path[pos.first][pos.second];
	}
	ranges::reverse(anses);
	for (auto [a, b] : anses)
		cout << a << " " << b << "\n";

}

