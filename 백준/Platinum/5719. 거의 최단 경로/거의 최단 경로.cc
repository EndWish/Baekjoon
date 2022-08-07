#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <tuple>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXN 500
#define pii pair<int,int>
#define tiib tuple<int,int,bool>

using namespace std;

int n, m;
int s, d;
array<vector<tiib>, MAXN> edge;	// 전체 경로 (거리, 다음노드, 활성화)
array<bool, MAXN> finished;	//확정되었는지 확인
array<int, MAXN> dp;	// s->d까지 거리의 최단거리
array<vector<pii>, MAXN> pre;	// 이전 노드와 (이전 노드 기준) 현재 노드로 오는 edge의 인덱스

void Reset();
void Dijkstra(int start);
void EraseEdge(int node);

int main() 
{

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int u, v, p;
	while (cin >> n >> m) {
		//초기화,입력값 받기
		if (n == 0 && m == 0) {
			break;
		}

		for (int i = 0; i < MAXN; ++i) {
			edge[i].clear();
		}
		Reset();

		cin >> s >> d;
		for (int i = 0; i < m; ++i) {
			cin >> u >> v >> p;
			edge[u].emplace_back(p, v, true);
		}

		//문제해결
		Dijkstra(s);
		EraseEdge(d);	//간선 제거
		Reset();
		Dijkstra(s);
		int res = dp[d];

		//출력
		if (res == numeric_limits<int>::max()) {
			cout << "-1\n";
		}
		else {
			cout << res << "\n";
		}

	}
	
}

void Reset() {
	finished.fill(false);
	dp.fill(numeric_limits<int>::max());
	for (auto& p : pre) {
		p.clear();
	}
}
void Dijkstra(int start) {
	priority_queue<pii> pq;	// -거리, 노드
	dp[start] = 0;
	pq.emplace(-0, start);

	while (!pq.empty()) {
		// 가장 가까운 노드를 확정시킨다.
		auto [dist, node] = pq.top();
		dist *= -1;
		pq.pop();

		if (finished[node])	// 이미 확정된 노드일 경우 스킵
			continue;
		finished[node] = true;
		//cout << format("{} 확정 : 거리-{}, 이전노드-{}\n", node, dp[node].first, dp[node].second);

		for (int i = 0; i < edge[node].size(); ++i) {
			auto [cost, nextNode, active] = edge[node][i];
			if (finished[nextNode] || !active) {	// 이미 확정되었거나 비활성화일 경우 스킵
				continue;
			}

			int nextDist = dist + cost;
			if (nextDist < dp[nextNode]) {	// 더 짧은 경로일 경우
				pre[nextNode].clear();
				pre[nextNode].emplace_back(node, i);
				dp[nextNode] = nextDist;
				pq.emplace(-nextDist, nextNode);
			}
			else if(nextDist == dp[nextNode]) {
				pre[nextNode].emplace_back(node, i);
			}
		}

	}

}

void EraseEdge(int node) {
	for (int i = 0; i < pre[node].size(); ++i) {
		auto [preNode, index] = pre[node][i];

		bool& active = get<2>(edge[preNode][index]);
		if (active) {
			active = false;
			//cout << format("{}-{} 간선 제거\n", preNode, node);
			EraseEdge(preNode);
		}
		
	}
}

