#include <iostream>
#include <vector>
#include <queue>

// 23290

using namespace std;

int f, s, g, u, d;
vector<int> dp;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> f >> s >> g >> u >> d;
	dp.assign(f + 1, -1);

	//문제해결
	queue<int> q;
	dp[s] = 0;
	q.push(s);
	while (!q.empty()) {
		int x = q.front();
		q.pop();

		int up = x + u;
		if (up <= f && dp[up] == - 1) {	// 건물을 넘지 않을 경우 && 방문하지 않았을 경우
			dp[up] = dp[x] + 1;
			q.push(up);
		}

		int down = x - d;
		if (1 <= down &&  dp[down] == -1) {	// 건물을 넘지 않을 경우 && 방문하지 않았을 경우
			dp[down] = dp[x] + 1;
			q.push(down);
		}
	}

	//출력
	if (dp[g] == -1)
		cout << "use the stairs";
	else
		cout << dp[g];

}