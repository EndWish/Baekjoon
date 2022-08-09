#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>

#define MAXN 201
#define pii pair<int,int>

using namespace std;

int n, m;
array<vector<pii>, MAXN> edge;
array<bool, MAXN> finished;
array<int, MAXN> dp;

float Dijkstra(int start);

int main() 
{

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;

	int s, e, l;
	for (int i = 0; i < m; ++i) {
		cin >> s >> e >> l;
		edge[s].emplace_back(l, e);
		edge[e].emplace_back(l, s);
	}

	//문제해결
	float ans = numeric_limits<float>::max();
	for (int i = 1; i <= n; ++i) {
		// ignition초기화
		finished.fill(false);
		dp.fill(numeric_limits<int>::max());
		ans = min(ans, Dijkstra(i));
	}

	//출력
	cout.precision(1);
	cout << fixed << ans;
	
}

float Dijkstra(int start) {
	priority_queue<pii> pq;	// -거리, 노드
	dp[start] = 0;
	pq.emplace(-0, start);
	while (!pq.empty()) {
		auto [dist, node] = pq.top();
		dist *= -1;
		pq.pop();

		if (finished[node])
			continue;
		finished[node] = true;

		for (auto [cost, nextNode] : edge[node]) {
			if (finished[nextNode]) {
				continue;
			}

			int nextDist = dist + cost;
			if (nextDist < dp[nextNode]) {
				dp[nextNode] = nextDist;
				pq.emplace(-nextDist, nextNode);
			}
		}
	}

	// 모든 정점을 태웠을때의 시간
	int nodeIgnite = *ranges::max_element(dp.begin() + 1, dp.begin() + n + 1);

	// 모든 정점을 태웠을때 아직 타지 않은 간선을 찾아 전부태우는 시간을 계산
	int edgeIgnite = 0;
	for (int i = 0; i < edge.size(); ++i) {
		for (auto [len, j] : edge[i]) {
			int Ignite1 = nodeIgnite - dp[i];	// i노드에서 부터 탄 거리
			int Ignite2 = nodeIgnite - dp[j];	// j노드에서 부터 탄 거리
			int lateLen = len - Ignite1 - Ignite2;
			if (lateLen > 0) {
				edgeIgnite = max(edgeIgnite, lateLen);
			}
		}
	}

	return (float)nodeIgnite + (float)edgeIgnite / 2.0f;
}
