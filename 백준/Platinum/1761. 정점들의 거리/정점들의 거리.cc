#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <cmath>

#define MAXN 40'001
#define MAXEXP 20
#define pii pair<int,int>

using namespace std;

int n, m;
array<vector<pii>, MAXN> edge;
array<array<pii, MAXEXP>, MAXN> parent;	// parent[node][i] : node의 2^i번째 조상의 node와 거리차
array<int, MAXN> depth;

void DFS(int node, int prev, int dist);
int LCA(int a, int b);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	int a, b, c;

	// 간선을 입력받는다.
	for (int i = 0; i < n - 1; ++i) {
		cin >> a >> b >> c;
		edge[a].emplace_back(c, b);
		edge[b].emplace_back(c, a);
	}

	//문제해결
	DFS(1, 0, 0);
	
	cin >> m;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		cout << LCA(a, b) << "\n";
	}

	//출력
	
}

void DFS(int node, int prev, int dist) {
	depth[node] = depth[prev] + 1;

	parent[node][0] = { prev, dist };
	for (int i = 1; i < MAXEXP; ++i) {
		int p = parent[parent[node][i - 1].first][i - 1].first;
		int d = parent[node][i - 1].second + parent[parent[node][i - 1].first][i - 1].second;
		parent[node][i] = { p ,d };
	}
	
	for (auto [d, next] : edge[node]) {
		if (next != prev) {
			DFS(next, node, d);
		}
	}
}

int LCA(int a, int b) {
	int res = 0;

	if (depth[a] < depth[b]) {	// a를 더 깊은것으로 바꾼다.
		swap(a, b);
	}

	// a를 b가 있는 곳 까지 이동시킨다. 예) 11칸 차이 = 8 + 2 + 1칸 순으로 이동할 것이다.
	for (int i = MAXEXP - 1; i >= 0; --i) {
		if (depth[a] - (1 << i) >= depth[b]) {
			res += parent[a][i].second;
			a = parent[a][i].first;
		}
	}

	if (a == b) {
		return res;
	}

	// 최소 공통 조상의 바로 직전까지 이동시킨다.
	for (int i = MAXEXP - 1 ; i >= 0; --i) {
		if (parent[a][i].first != parent[b][i].first) {	// a와 b의 2^i번째 조상이 다르면 그만큼 올라온다. 
			res += parent[a][i].second + parent[b][i].second;
			a = parent[a][i].first;
			b = parent[b][i].first;
		}
	}

	res += parent[a][0].second + parent[b][0].second;
	//a = parent[a][0].first;	// 최소 공통 조상의 노드가 필요한 문제의 경우 이것도 같이 리턴하면 된다.
	//b = parent[b][0].first;
	return res;
}

