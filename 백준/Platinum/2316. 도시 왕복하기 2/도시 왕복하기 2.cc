#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXN 401

int n, p;
array<vector<int>, MAXN> edges;
array<array<int, MAXN>, MAXN> capacity, flow;
array<bool, MAXN> visit;
array<int, MAXN> path;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> p;
	for (int i = 0; i < p; ++i) {
		int u, v;
		cin >> u >> v;
		edges[u].push_back(v);
		edges[v].push_back(u);
		capacity[u][v] = 1;
		capacity[v][u] = 1;
	}

	//문제해결
	int ans = 0;
	while (true) {
		fill_n(&path[0], MAXN, -1);

		queue<pair<int, bool>> q;	// 노드, 역류여부
		q.emplace(1, false);
		while (!q.empty()) {
			auto [node, reverse] = q.front();
			q.pop();

			if (node == 2)
				break;

			for (int nextNode : edges[node]) {
				if (path[nextNode] == -1 && flow[node][nextNode] < capacity[node][nextNode]) {
					if (reverse && 0 <= flow[node][nextNode])
						continue;

					path[nextNode] = node;
					if (!visit[node] && visit[nextNode])
						q.emplace(nextNode, true);
					else
						q.emplace(nextNode, false);
				}
			}
		}

		if (path[2] != -1) {	// 경로가 존재하는 경우
			for (int node = 2, nextNode = -1; node != 1; nextNode = node, node = path[node]) {
				int preNode = path[node];
				visit[node] = true;
				if (flow[preNode][node] == -1 && flow[node][nextNode] == -1)
					visit[node] = false;

				++flow[preNode][node];
				--flow[node][preNode];
			}
			++ans;
		}
		else {	// 경로가 존재하지 않는 경우
			break;
		}
	}

	cout << ans;

}