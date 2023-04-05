#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define INF numeric_limits<int>::max()

int n, k;
vector<vector<int>> edges;
vector<vector<int>> dp;		// dp[방문한 행성들][현재 위치] = 최소 시간

void FloydWarshall();
int GetDP(int bit, int pos);
int GetOneBit(int bit);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> k;
	edges.assign(n, vector<int>(n, 0));
	dp.assign((1 << n), vector<int>(n, -1));
	for (auto& vec : edges)
		for (auto& edge : vec)
			cin >> edge;
	
	FloydWarshall();

	dp[1 << k][k] = 0;

	int ans = INF;
	for (int pos = 0; pos < n; ++pos) {
		int dist = GetDP((1 << n) - 1, pos);
		if (dist < 0)
			continue;
		ans = min(ans, dist);
	}
	cout << ans;

}

void FloydWarshall() {
	for (int via = 0; via < n; ++via) {
		for (int s = 0; s < n; ++s) {
			for (int e = 0; e < n; ++e) {
				if (s == e)
					continue;

				int viaDist = edges[s][via] + edges[via][e];
				if (viaDist < edges[s][e])
					edges[s][e] = viaDist;
			}
		}
	}
}
int GetDP(int bit, int pos) {
	if (dp[bit][pos] != -1)	// 이미 값을 구했다면
		return dp[bit][pos];

	if (GetOneBit(bit) <= 1)
		return dp[bit][pos] = -2;

	int result = INF;
	for (int prevPos = 0; prevPos < n; ++prevPos) {
		if ((1 << prevPos & bit) && prevPos != pos) {	//	방문한 적이 있고 현재 위치가 아닐 경우
			int prevBit = bit ^ (1 << pos);

			int prevDP = GetDP(prevBit, prevPos);
			if (prevDP < 0)	// 불가능한 경우는 무시
				continue;
			result = min(result, prevDP + edges[prevPos][pos]);
		}
	}

	if (result == INF)
		dp[bit][pos] = -2;
	else
		dp[bit][pos] = result;
	return dp[bit][pos];
}
int GetOneBit(int bit) {
	int result = 0;
	while (0 < bit) {
		++result;
		bit &= (bit - 1);
	}
	return result;
}