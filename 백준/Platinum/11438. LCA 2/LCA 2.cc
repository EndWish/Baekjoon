#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>

#define MAXN 100'001
#define MAXE 18	

using namespace std;

int n, m;
array<vector<int>, MAXN> edge;
array<int, MAXN> depth;
array<array<int, MAXE>, MAXN> parent;

void DFS(int index, int prev);
int LCA(int a, int b);

int main() 
{

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;

	int a, b;
	for (int i = 0; i < n - 1; ++i) {
		cin >> a >> b;
		edge[a].push_back(b);
		edge[b].push_back(a);
	}

	//문제해결
	DFS(1, 0);
	cin >> m;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		cout << LCA(a, b) << "\n";
	}

	//출력
	
}

void DFS(int index, int prev) {
	depth[index] = depth[prev] + 1;
	parent[index][0] = prev;

	for (int i = 1; i < MAXE; ++i) {
		parent[index][i] = parent[parent[index][i - 1]][i - 1];
	}

	for (int next : edge[index]) {
		if (next != prev) {
			DFS(next, index);
		}
	}
}

int LCA(int a, int b) {
	if (depth[a] < depth[b]) {
		swap(a, b);
	}

	for (int i = MAXE - 1; i >= 0; --i) {
		if (depth[a] - (1 << i) >= depth[b]) {
			a = parent[a][i];	// a의 2^i 번째 조상으로 이동
		}
	}

	if (a == b) {
		return a;
	}

	for (int i = MAXE - 1; i >= 0; --i) {
		if (parent[a][i] != parent[b][i]) {
			a = parent[a][i];
			b = parent[b][i];
		}
	}
	a = parent[a][0];
	b = parent[b][0];

	return a;
}
