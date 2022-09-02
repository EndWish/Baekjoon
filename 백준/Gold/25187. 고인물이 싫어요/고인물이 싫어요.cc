#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXN 100'001

using namespace std;

int n, m, q;
int water[MAXN];
vector<vector<int>> edge;
int parent[MAXN];
int clean[MAXN];
bool visit[MAXN];

void DFS(int node, int root);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m >> q;
	edge.assign(n + 1, {});
	iota(&parent[0], &parent[0] + MAXN, 0);

	for (int i = 1; i <= n; ++i)
		cin >> water[i];

	int u, v;
	for (int i = 0; i < m; ++i) {
		cin >> u >> v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}

	//문제해결
	for (int node = 1; node <= n; ++node) {
		if (!visit[node]) {
			DFS(node, node);
		}
	}

	//출력
	int k;
	for (int i = 0; i < q; ++i) {
		cin >> k;
		if (clean[parent[k]] > 0)
			cout << "1\n";
		else
			cout << "0\n";
	}

}

void DFS(int node, int root) {
	visit[node] = true;
	parent[node] = root;
	if (water[node] == 1) {	// 청정수일 경우
		++clean[root];
	}
	else {	// 고인물일 경우
		--clean[root];
	}

	for (auto nextNode : edge[node]) {
		if (!visit[nextNode])
			DFS(nextNode, root);
	}
}