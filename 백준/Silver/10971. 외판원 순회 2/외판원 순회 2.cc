#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int n;
int w[10][10];
int dp[10][1 << 11];	// dp[a][b] = 현재a도시에 있고 b의 도시들을 방문했을 때 최소값

int DP(int cur, int visit);

int main()
{

	ios_base::sync_with_stdio(false); cin.tie(NULL);
	
	//초기화 & 입력받기
	cin >> n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> w[j][i];
		}
	}

	//문제해결
	cout << DP(0, (1 << n) - 1);

	//출력

}

int DP(int cur, int visit) {

	if (dp[cur][visit] != 0) {
		return dp[cur][visit];
	}

	int preVisit = visit ^ (1 << cur);
	if (preVisit == 0) {
		if (w[0][cur] == 0) {
			dp[cur][visit] = INT_MAX;
		}
		else {
			dp[cur][visit] = w[0][cur];
		}
		return dp[cur][visit];
	}

	dp[cur][visit] = INT_MAX;
	for (int i = 0; i < n; ++i) {
		if ((preVisit & (1 << i)) != 0) {	//i도시를 방문 했었더라면

			if (w[i][cur] == 0) {	// i도시에서 현재도시로 오는 것이 불가능하면 스킵
				continue;
			}
			if (DP(i, preVisit) == INT_MAX) {
				continue;
			}

			dp[cur][visit] = min(dp[cur][visit], DP(i, preVisit) + w[i][cur]);
		}
	}

	return dp[cur][visit];
}
