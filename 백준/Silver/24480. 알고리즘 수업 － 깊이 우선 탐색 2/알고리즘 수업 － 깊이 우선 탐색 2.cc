#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n, m, r;
array<vector<int>, 100'001> edges;
array<int, 100'001> visit;
int cnt;

void DFS(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m >> r;
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		edges[u].push_back(v);
		edges[v].push_back(u);
	}

	for (int node = 1; node <= n; ++node) {
		ranges::sort(edges[node], greater<int>{});
	}

	//문제해결
	DFS(r);

	for (int i = 1; i <= n; ++i)
		cout << visit[i] << "\n";

}

void DFS(int node) {
	visit[node] = ++cnt;

	for (int nextNode : edges[node]) {
		if (visit[nextNode] == 0)
			DFS(nextNode);
	}
}
