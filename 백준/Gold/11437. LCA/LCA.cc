#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

int n, m;
array < vector<int>, 50'001> edge;
array< int, 50'001> depth;

void DFS(int node, int curDepth, int parent);
int LCA(int a, int b);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	int a, b;

	edge[1].push_back(0);	// 루트는 부모가 없기 때문에 버퍼를 하나 넣어줌 [DFS 참고]
	for (int i = 0; i < n - 1; ++i) {
		cin >> a >> b;
		edge[a].push_back(b);
		edge[b].push_back(a);
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

void DFS(int node, int curDepth, int parent) {
	depth[node] = curDepth;
	if (parent != 0) {	// 부모는 edge[node]의 첫번째 원소로 오도록 이동시킨다.
		auto p = ranges::find(edge[node], parent);
		swap(*p, *edge[node].begin());
	}

	for (int child : edge[node] | views::drop(1)) {	// 부모인 첫번째 원소를 무시하고 자식들을 DFS수행 (루트인 1은 부모가 없기 때문에 버퍼를 하나 넣어줬다.)
		DFS(child, curDepth + 1, node);
	}
}

int LCA(int a, int b) {
	int aDepth = depth[a];
	int bDepth = depth[b];
	if (aDepth < bDepth) {
		swap(aDepth, bDepth);
		swap(a, b);
	}

	while (aDepth > bDepth) {	// 같은 깊이가 될때까지 부모로 이동
		a = edge[a][0];
		--aDepth;
	}

	while (a != b) {
		a = edge[a][0];
		b = edge[b][0];
	}
	return a;
}
