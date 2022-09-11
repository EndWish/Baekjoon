#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXN 1001
#define INF numeric_limits<int>::max()
#define pii pair<int,int>

using namespace std;

int n, m, x;
array<vector<pii>, MAXN> edge, edge2;	//  edge2는 edge의 역방향 그래프인다.(=각각의 집에서 파티로 가는 최단경로를 역산하여 구한다.)
int dp[MAXN];
bool finished[MAXN];

array<int, MAXN> ans;

void Daijkstra(int start, array<vector<pii>, MAXN>& graph);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m >> x;
	int u, v, w;
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> w;
		edge[u].emplace_back(w, v);
		edge2[v].emplace_back(w, u);
	}

	//문제해결
	
	Daijkstra(x, edge);	// 파티에서 집가는 경로의 최소 거리
	for (int i = 1; i <= n; ++i) {
		ans[i] += dp[i];
	}
	Daijkstra(x, edge2);	// 파티에서 집가는 경로의 최소 거리
	for (int i = 1; i <= n; ++i) {
		ans[i] += dp[i];
	}

	//출력
	cout << *ranges::max_element(ans.begin() + 1, ans.begin() + n + 1);

}

void Daijkstra(int start, array<vector<pii>, MAXN>& graph) {
	fill_n(&dp[0], MAXN, INF);
	fill_n(&finished[0], MAXN, false);

	priority_queue<pii> pq;
	dp[start] = 0;
	pq.emplace(-0, start);
	while (!pq.empty()) {
		auto [dist, node] = pq.top();
		dist *= -1;
		pq.pop();

		if (finished[node])
			continue;
		finished[node] = true;

		for (auto [cost, nextNode] : graph[node]) {
			if (finished[nextNode])
				continue;
			int nextDist = dist + cost;
			if (nextDist < dp[nextNode]) {
				dp[nextNode] = nextDist;
				pq.emplace(-nextDist, nextNode);
			}
		}
	}

}
