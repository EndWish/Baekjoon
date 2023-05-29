#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>

using namespace std;

#define INF numeric_limits<int>::max()

int n;
array<vector<int>, 3001> edges;
array<int, 3001> dist;
array<int, 3001> visit;
queue<int> q;

int cnt;

void InitDist();
int DFS(int node, int prevNode);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	int u, v;
	for (int i = 0; i < n; ++i) {
		cin >> u >> v;
		edges[u].push_back(v);
		edges[v].push_back(u);
	}

	InitDist();

	for (int i = 1; i <= n; ++i) {
		cout << dist[i] << " ";
	}
	
}

void InitDist() {
	fill_n(&dist[0], 3001, -1);
	fill_n(&visit[0], 3001, -1);

	DFS(1, 0);

	while (!q.empty()) {
		int node = q.front();
		q.pop();

		for (int nextNode : edges[node]) {
			if (dist[nextNode] == -1) {
				dist[nextNode] = dist[node] + 1;
				q.push(nextNode);
			}
		}
	}

}

int DFS(int node, int prevNode) {
	visit[node] = ++cnt;

	for (int nextNode : edges[node]) {
		if (nextNode == prevNode)
			continue;

		if (visit[nextNode] != -1) {
			dist[node] = 0;
			q.push(node);
			return visit[nextNode];
		}
		else {
			int result = DFS(nextNode, node);

			if (result <= visit[node]) {
				dist[node] = 0;
				q.push(node);
				return result;
			}
		}
	}

	return visit[node];
}
