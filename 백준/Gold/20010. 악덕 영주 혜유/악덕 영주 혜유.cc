#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include <queue>
#include <ranges>

//20010

#define MAXN 1000
#define pii pair<int,int>

using namespace std;

int n, k;
vector<pii> edge[MAXN];	// 비용, 도작지
vector<pii> mst[MAXN];	// 비용, 도작지
array<bool, MAXN> visit;

int buildCost;

pii DFS(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> k;
	int v1, v2, c;
	for (int i = 0; i < k; ++i) {
		cin >> v1 >> v2 >> c;
		edge[v1].emplace_back(c, v2);
		edge[v2].emplace_back(c, v1);
	}

	//문제해결
	// 1. prim 알고리즘 사용
	priority_queue<tuple<int,int,int>> pq;	// -비용, 이전마을, 이후마을
	pq.push({ -0, 0, 0 });
	while (!pq.empty()) {
		auto [cost, x, y] = pq.top();
		cost *= -1;
		pq.pop();

		if (visit[y])	// 이미 방문했을 경우
			continue;
		
		visit[y] = true;	// 방문처리
		buildCost += cost;	// 건설비용에 추가

		auto isNotVisit = [](pii& arg) { return !visit[arg.second]; };	// 방문을 하지 않은 곳인지 확인하는 pred함수
		
		for (auto& [cost2, z] : edge[y] | views::filter(isNotVisit) ) {
			pq.emplace(-cost2, y, z);	// pq에 삽입
		}

		// mst에 추가
		if (x != y) {
			mst[x].emplace_back(cost, y);
			mst[y].emplace_back(cost, x);
		}
		
	}

	// 2. DFS 사용
	fill_n(visit.begin(), n, false);
	int startNode = DFS(0).first;
	fill_n(visit.begin(), n, false);
	int worstMoveCost = DFS(startNode).second;

	//출력
	cout << buildCost << "\n" << worstMoveCost;

}

pii DFS(int x)	// 노드와 최대 비용 리턴
{
	visit[x] = true;

	int maxDest = x;
	int maxCost = 0;
	for (int i = 0; i < mst[x].size(); ++i) {
		auto [costY, y] = mst[x][i];	// 연결된 노드의 정보를 가져온다.
		if (!visit[y]) {	// 방문을 하지 않은 곳이면
			auto [DFSdest, DFScost] = DFS(y);
			DFScost += costY;	// 현재 노드(x)에서 다음노드(y)로 가는 비용을 추가 
			if (maxCost < DFScost) {
				maxCost = DFScost;
				maxDest = DFSdest;
			}
		}
	}

	return make_pair(maxDest, maxCost);
}
