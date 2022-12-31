#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long
#define pll pair<ll,ll>
#define MAXN 10'001

int n, m, k;
array<vector<pll>, MAXN> edges;		// 비용, 다음 노드
array<array<ll, 21>, MAXN> finished;	// 노드, 포장횟수

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	ranges::fill_n(&finished[0][0], 21 * MAXN, -1);
	cin >> n >> m >> k;
	for (int i = 0; i < m; ++i) {
		int u, v, c;
		cin >> u >> v >> c;
		edges[u].emplace_back(c, v);
		edges[v].emplace_back(c, u);
	}
	
	//문제해결
	priority_queue<pair<ll, pll>, vector<pair<ll, pll>> ,greater<>> pq;		// 거리, 노드, 포장횟수
	pq.emplace(0, make_pair(1, 0));
	while (!pq.empty()) {
		ll dist = pq.top().first;
		ll node = pq.top().second.first;
		ll cover = pq.top().second.second;

		pq.pop();

		if (finished[node][cover] != -1)
			continue;
		finished[node][cover] = dist;	// 확정
		//cout << "노드:" << node << ", 포장횟수:" << cover << "  -  " << dist << "확정\n";

		for (auto [cost, nextNode] : edges[node]) {
			// 포장하지 않는 경우
			if (finished[nextNode][cover] == -1) {
				pq.emplace(dist + cost, make_pair(nextNode, cover));
			}

			// 포장하는 경우
			if (finished[nextNode][cover + 1] == -1 && cover < k) {
				pq.emplace(dist, make_pair(nextNode, cover + 1));
			}
		}

	}

	//출력
	ll ans = numeric_limits<ll>::max();
	for (int i = 0; i <= k; ++i) {
		if(finished[n][i] != -1)
			ans = min(ans, finished[n][i]);
	}
	cout << ans;

}
