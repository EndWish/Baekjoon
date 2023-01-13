#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXN 100'001

int t, n, m;
int idCount;
array<vector<int>, MAXN> edges;
array<int, MAXN> belong;
array<int, MAXN> visit;
stack<int> s;

vector<vector<int>> SCC;

int DFS(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> t;
	while (t-- > 0) {
		//초기화,입력값 받기
		belong.fill(-1);
		visit.fill(-1);
		idCount = 0;
		for (auto& vec : edges)
			vec.clear();
		SCC.clear();

		cin >> n >> m;
		int u, v;
		for (int i = 0; i < m; ++i) {
			cin >> u >> v;
			edges[u].push_back(v);
		}

		//문제해결
		for (int node = 1; node <= n; ++node) {
			if(visit[node] == -1)
				DFS(node);
		}

		int ans = SCC.size();
		vector<bool> hand(SCC.size(), true);
		for (int node = 1; node <= n; ++node) {
			for (int edge : edges[node]) {
				if (belong[node] != belong[edge] && hand[belong[edge]]) {
					//cout << node << "->" << edge << "로 이동가능\n";
					--ans;
					hand[belong[edge]] = false;
				}
			}
		}

		//출력
		cout << ans << "\n";

	}


}

int DFS(int node) {
	visit[node] = ++idCount;
	s.push(node);

	int parent = visit[node];

	for (int edge : edges[node]) {
		if (visit[edge] == -1)	// 아직 방문하지 않은 경우
			parent = min(parent, DFS(edge));
		else if (belong[edge] == -1)	// 방문은 했지만 아직 확정되지 않은 경우(사이클)
			parent = min(parent, visit[edge]);
	}

	if (visit[node] == parent) {
		vector<int> scc;
		while (true) {
			int x = s.top();
			s.pop();
			scc.push_back(x);
			belong[x] = SCC.size();
			if (x == node)
				break;
		}
		SCC.push_back(move(scc));
	}

	return parent;
}
