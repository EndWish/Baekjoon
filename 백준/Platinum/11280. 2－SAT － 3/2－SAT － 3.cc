#include <iostream>
#include <vector>
#include <stack>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>



using namespace std;

int n, m;
vector<vector<int>> edge;
vector<int> visit;
vector<bool> finished;
stack<int> s;
vector<vector<int>> SCC;
int id = 0;

int DFS(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	edge.assign(n * 2 + 1, {});
	finished.assign(n * 2 + 1, false);
	visit.assign(n * 2 + 1, 0);

	int a, b;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		edge[n - a].push_back(b);	// !a => b
		edge[n - b].push_back(a);	// !b => a
	}

	//문제해결
	for (int node = 1; node <= n; ++node) {
		if (!finished[n + node])
			DFS(node);
		if (!finished[n - node])
			DFS(-node);
	}

	bool ans = true;
	for (auto& scc : SCC) {
		ranges::sort(scc);
		int s = 0; int e = scc.size() - 1;
		while (s < e) {
			int sum = scc[s] + scc[e];
			if (sum == 0) {// ~a 와 a 가 같이 있어서 불가능한 경우
				ans = false;
				break;
			}
			else if (sum < 0)
				++s;
			else
				--e;
		}
	}

	//출력

	if (ans)
		cout << 1;
	else
		cout << 0;

}

int DFS(int node) {
	visit[n + node] = ++id;
	s.push(node);
	int parent = visit[n + node];
	for (int i = 0; i < edge[n + node].size(); ++i) {
		int nextNode = edge[n + node][i];
		if (!finished[n + nextNode]) {
			if (visit[n + nextNode] == 0) {	// 방문하지 않은 곳일 경우
				parent = min(parent, DFS(nextNode));
			}
			else {
				parent = min(parent, visit[n + nextNode]);
			}
		}
	}

	if (parent == visit[n + node]) {
		vector<int> scc;
		while (true) {
			int t = s.top();
			s.pop();
			scc.push_back(t);
			finished[n + t] = true;
			if (t == node)
				break;
		}
		SCC.push_back(scc);
	}

	return parent;
}
