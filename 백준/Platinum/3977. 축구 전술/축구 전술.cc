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
array<vector<int>,MAXN> edges;
array<int, MAXN> visit, belong;
int idCount;
stack<int> s;
vector<vector<int>> SCC;

int DFS(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> t;
	while (t-- > 0) {
		//초기화,입력값 받기
		visit.fill(-1);
		belong.fill(-1);
		SCC.clear();
		edges.fill({});

		cin >> n >> m;
		for (int i = 0; i < m; ++i) {
			int u, v;
			cin >> u >> v;
			edges[u].push_back(v);
		}

		//문제해결
		for (int node = 0; node < n; ++node) {
			if (visit[node] == -1)
				DFS(node);
		}

		int nPreceding = SCC.size();
		vector<bool> precedings(SCC.size(), true);
		for (int node = 0; node < n; ++node) {
			for (int edge : edges[node]) {
				if (belong[node] != belong[edge] && precedings[belong[edge]]) {
					precedings[belong[edge]] = false;
					--nPreceding;
				}
			}
		}

		//출력
		if (nPreceding == 1) {
			int index = ranges::distance(precedings.begin(), ranges::find(precedings, true));
			ranges::sort(SCC[index]);
			for (int ans : SCC[index])
				cout << ans << "\n";
		}
		else if(nPreceding > 1) {
			cout << "Confused\n";
		}
		cout << "\n";
	}


}

int DFS(int node) {
	visit[node] = ++idCount;
	s.push(node);

	int parent = visit[node];
	for (int edge : edges[node]) {
		if (visit[edge] == -1)
			parent = min(parent, DFS(edge));
		else if (belong[edge] == -1)
			parent = min(parent, visit[edge]);
	}

	if (parent == visit[node]) {
		vector<int> scc;
		while (true) {
			int x = s.top();
			s.pop();
			belong[x] = SCC.size();
			scc.push_back(x);
			if (x == node)
				break;
		}
		SCC.push_back(move(scc));
	}

	return parent;
}
