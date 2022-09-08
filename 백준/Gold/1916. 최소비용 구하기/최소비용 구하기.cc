#include <iostream>
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXN 1001
#define INF numeric_limits<int>::max()
#define pii pair<int,int>

using namespace std;

int n, m;
int s, e;
vector<pii> edge[MAXN];
bool finished[MAXN];
int dp[MAXN];

void Daijkstra(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	int u, v, c;
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> c;
		edge[u].emplace_back(c, v);
	}
	cin >> s >> e;

	//문제해결
	Daijkstra(s);

	//출력
	cout << dp[e];

}

void Daijkstra(int node) {
	fill_n(&dp[0], MAXN, INF);

	priority_queue<pii> pq;
	dp[node] = 0;
	pq.emplace(-0, node);
	while (!pq.empty()) {
		auto [dist, node] = pq.top();
		dist *= -1;
		pq.pop();

		if (finished[node])
			continue;
		finished[node] = true;

		for (auto [cost, nextNode] : edge[node]) {
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
