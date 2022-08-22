#include <iostream>
#include <vector>
#include <span>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXN 501
#define INF numeric_limits<int>::max()
#define pii pair<int,int>

using namespace std;

int n, m, w;
vector<pii> edge[MAXN];	// = {코스트, 다음 노드}
int dp[MAXN];
vector<pair<pii, int>> checking;

int BellmanFord(int start, int end);
void BellmanFordCycle();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int tc;
	cin >> tc;
	while (tc-- > 0) {
		//초기화,입력값 받기
		for (int i = 0; i < MAXN; ++i) {
			edge[i].clear();
		}
		checking.clear();

		cin >> n >> m >> w;
		int s, e, t;
		for (int i = 0; i < m; ++i) {
			cin >> s >> e >> t;
			edge[s].emplace_back(t, e);
			edge[e].emplace_back(t, s);
		}

		//문제해결

		for (int i = 0; i < w; ++i) {
			cin >> s >> e >> t;
			edge[s].emplace_back(-t, e);
			checking.push_back({ { s, e }, t });
		}

		bool possible = false;
		for (auto [uv, t] : checking) {
			if (BellmanFord(uv.second, uv.first) < t) {
				possible = true;
				break;
			}
		}

		//출력
		if (possible) {
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}
	}

}

int BellmanFord(int start, int end) {
	ranges::fill(span(dp), INF);
	dp[start] = 0;
	for (int i = 0; i < n - 1; ++i) {	// n-1번 수행
		BellmanFordCycle();
	}
	return dp[end];
}

void BellmanFordCycle() {
	for (int node = 1; node <= n; ++node) {	// 모든 간선들을 순환하면서
		for (auto [cost, nextNode] : edge[node]) {
			if (dp[node] != INF && dp[node] + cost < dp[nextNode]) {
				dp[nextNode] = dp[node] + cost;	// 최단거리 업데이트
			}
		}
	}
}
