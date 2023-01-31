#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

const int offset = 1000;

int n, m;
array<vector<int>, 2001> edges;
array<int, 2001> belong;
array<int, 2001> visit;
vector<vector<int>> SCCs;

stack<int> st;
int cnt;

int DFS(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	while (cin >> n >> m) {
		//초기화,입력값 받기
		edges.fill({});
		belong.fill(-1);
		visit.fill(-1);
		SCCs.clear();

		for (int i = 0; i < m; ++i) {
			int a, b;
			cin >> a >> b;
			edges[offset - a].push_back(offset + b);
			edges[offset - b].push_back(offset + a);
		}

		//문제해결
		for (int i = 1; i <= n; ++i) {
			int node = offset + i;
			int notNode = offset - i;
			if (belong[node] == -1)
				DFS(node);
			if (belong[notNode] == -1)
				DFS(notNode);
		}
		
		// ~x 와 x가 같은 SCC인 경우
		bool success = true;
		for (int i = 1; i <= n; ++i) {
			if (belong[offset + i] == belong[offset - i]) {
				success = false;
				//cout << "~x 와 x가 같은 SCC인 경우\n";
				break;
			}	
		}
		if (belong[offset + 1] > belong[offset - 1]) {
			//cout << "상근이가 진출할 수 없는 경우 "<< belong[offset + 1] << " -> " << belong[offset - 1] << "\n";
			success = false;
		}

		if (success)
			cout << "yes\n";
		else
			cout << "no\n";

	}


	
}

int DFS(int node) {
	visit[node] = ++cnt;
	st.push(node);

	int parent = visit[node];
	for (int nextNode : edges[node]) {
		if (visit[nextNode] == -1)
			parent = min(parent, DFS(nextNode));
		else if (belong[nextNode] == -1)
			parent = min(parent, visit[nextNode]);
	}

	if (visit[node] == parent) {
		vector<int> SCC;
		while (true) {
			int x = st.top();
			st.pop();
			SCC.push_back(x);
			belong[x] = SCCs.size();
			if (x == node)
				break;
		}
		SCCs.push_back(move(SCC));
	}

	return parent;
}
