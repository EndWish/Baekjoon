#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define MAXN 20'001

int n, m;
array<vector<int>, MAXN> edges;
array<int, MAXN> depth;

void BFS(int start);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	int a, b;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}

	//문제해결
	BFS(1);

	int node = 0, dist = -1, same = 0;
	for (int i = n; i > 0; --i) {
		if (depth[i] > dist) {
			node = i;
			dist = depth[i];
			same = 1;
		}
		else if (depth[i] == dist) {
			node = i;
			++same;
		}
	}

	//출력
	cout << node << " " << dist << " " << same;

}

void BFS(int start) {
	depth.fill(-1);

	queue<int> q;
	q.push(start);
	depth[start] = 0;

	while (!q.empty()) {
		int node = q.front();
		q.pop();

		for (int nextNode : edges[node]) {
			if (depth[nextNode] == -1) {
				q.push(nextNode);
				depth[nextNode] = depth[node] + 1;
			}
		}
	}
}
