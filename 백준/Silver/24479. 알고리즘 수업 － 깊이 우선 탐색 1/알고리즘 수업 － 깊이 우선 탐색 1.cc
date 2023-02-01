#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n, m, r;
array<vector<int>, 100'001> edges;
array<bool, 100'001> visit;
array<int, 100'001> ans;

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
	for (int i = 1; i <= n; ++i) {
		ranges::sort(edges[i]);
	}

	//문제해결
	DFS(r);
	for (int i = 1; i <= n; ++i) {
		cout << ans[i] << "\n";
	}
	
}

void DFS(int node) {
	ans[node] = ++cnt;
	visit[node] = true;
	for (int nextNode : edges[node]) {
		if (!visit[nextNode])
			DFS(nextNode);
	}
}
