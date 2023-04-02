#include <iostream>
#include <vector>
#include <stack>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define pii pair<int,int>

int n;
array<int, 101> edges, visit;
array<bool, 101> finished;
stack<int> st;
int cnt;

vector<vector<int>> SCCs;

int DFS(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> edges[i];

	for (int i = 1; i <= n; ++i)
		if (!finished[i])
			DFS(i);

	vector<int> ans;
	for (auto& SCC : SCCs)
		for (int num : SCC)
			ans.push_back(num);

	ranges::sort(ans);
	cout << ans.size() << "\n";
	for (int num : ans)
		cout << num << "\n";
}

int DFS(int node) {	// 사이클의 시작 노드, 개수
	st.push(node);
	visit[node] = ++cnt;
	int parent = visit[node];
	int nextNode = edges[node];

	if (!finished[nextNode]) {
		if (visit[nextNode] != 0)
			parent = min(parent, visit[nextNode]);
		else
			parent = min(parent, DFS(nextNode));
	}

	if (visit[node] == parent) {
		vector<int> SCC;
		while (true) {
			int x = st.top();
			st.pop();
			SCC.push_back(x);
			if (x == node)
				break;
		}

		if(1 < SCC.size() || node == nextNode)
			 SCCs.push_back(SCC);
	}

	finished[node] = true;
	return parent;
}
