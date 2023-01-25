#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXN 5'001

int n, m;
array<vector<int>, MAXN> edges;
array<int, MAXN> visit;
array<int, MAXN> belong;
vector<vector<int>> SCCs;

stack<int> s;
int idCnt;

int DFS(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	while (true) {
		//초기화,입력값 받기
		idCnt = 0;
		edges.fill({});
		visit.fill(-1);
		belong.fill(-1);
		SCCs.clear();

		cin >> n;
		if (n == 0)
			break;
		cin >> m;
		for (int i = 0; i < m; ++i) {
			int u, v;
			cin >> u >> v;
			edges[u].push_back(v);
		}

		//문제해결
		for (int i = 1; i <= n; ++i) {
			if (belong[i] == -1)
				DFS(i);
		}

		vector<int> leaf(MAXN, true);
		for (int node = 1; node <= n; ++node) {
			for (int nextNode : edges[node]) {
				if (belong[node] != belong[nextNode])
					leaf[belong[node]] = false;
			}
		}

		vector<int> ans;
		for (int i = 0; i < SCCs.size(); ++i) {
			if (leaf[i]) {
				for (int node : SCCs[i])
					ans.push_back(node);
			}
		}
		ranges::sort(ans);
		for (int x : ans)
			cout << x << " ";
		cout << "\n";

	}

	
}

int DFS(int node) {
	visit[node] = ++idCnt;
	s.push(node);

	int parent = visit[node];
	for (int nextNode : edges[node]) {
		if (visit[nextNode] == -1)
			parent = min(parent, DFS(nextNode));
		else if (belong[nextNode] == -1)
			parent = min(parent, visit[nextNode]);
	}

	if (parent == visit[node]) {
		vector<int> SCC;
		while (true) {
			int x = s.top();
			s.pop();

			SCC.push_back(x);
			belong[x] = SCCs.size();

			if (x == node)
				break;
		}
		SCCs.push_back(move(SCC));
	}

	return parent;
}
