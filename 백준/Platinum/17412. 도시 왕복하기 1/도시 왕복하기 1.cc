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
array<array<int, MAXN>, MAXN> capacity;
array<array<int, MAXN>, MAXN> flow;
array<int, MAXN> preNodes;
array<vector<int>, MAXN> edges;

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
		//capacity[v][u] = 0;
	}

	//문제해결
	queue<int> q;
	while (true) {
		fill_n(&preNodes[0], MAXN, -1);
		q.push(1);
		while (!q.empty()) {
			int node = q.front();
			q.pop();
			for (int nextNode : edges[node]) {
				// 아직 방문하지 않았고 흐를 수 있을 경우
				if (preNodes[nextNode] == -1 && flow[node][nextNode] < capacity[node][nextNode]) {
					q.push(nextNode);
					preNodes[nextNode] = node;
				}
			}
		}

		// 더이상 경로가 없을 경우
		if (preNodes[2] == -1)
			break;

		// 흐를수 있는 물의 양을 측정한다.
		int add = numeric_limits<int>::max();
		for (int node = 2; node != 1; node = preNodes[node]) {
			int preNode = preNodes[node];
			add = min(add, capacity[preNode][node] - flow[preNode][node]);
		}

		for (int node = 2; node != 1; node = preNodes[node]) {
			int preNode = preNodes[node];
			flow[preNode][node] += add;
			flow[node][preNode] -= add;
		}
	}

	int ans = 0;
	for (int nextNode : edges[1]) {
		ans += flow[1][nextNode];
	}
	cout << ans;

}
