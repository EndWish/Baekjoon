#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define MAXN 100

int n, m;
vector<int> edges1[MAXN];
vector<int> edges2[MAXN];
array<bool, MAXN> visit;

int DFS(int node, vector<int>* edges);
int SubDFS(int node, vector<int>* edges);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	int u, v;
	for (int i = 0; i < m; ++i) {
		cin >> u >> v;
		edges1[v].push_back(u);
		edges2[u].push_back(v);
	}

	//문제해결
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		int mid = (n + 1) / 2;
		if (mid <= DFS(i, edges1) || mid <= DFS(i, edges2)) {
			++ans;
		}
	}

	//출력
	cout << ans;

}

int DFS(int node, vector<int>* edges) {
	visit.fill(false);
	return SubDFS(node, edges) - 1;
}

int SubDFS(int node, vector<int>* edges) {
	int result = 1;
	visit[node] = true;

	for (int nextNode : edges[node]) {
		if (!visit[nextNode]) {
			result += SubDFS(nextNode, edges);
		}
	}
	return result;
}
