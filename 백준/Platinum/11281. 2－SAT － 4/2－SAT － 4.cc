#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <set>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

const int offset = 10'000;

int n, m;
array<vector<int>, 20'001> edges;
array<int, 20'001> belong;
array<int, 20'001> visit;
vector<vector<int>> SCCs;

int cnt;
stack<int> st;
int DFS(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	visit.fill(-1);
	belong.fill(-1);

	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int j, k;
		cin >> j >> k;
		edges[-j + offset].push_back(k + offset);
		edges[-k + offset].push_back(j + offset);
	}

	//문제해결
	for (int i = -n; i <= n; ++i) {
		if (i == 0)
			continue;
		int node = i + offset;
		if (belong[node] == -1)
			DFS(node);
	}
	
	// 불가능한 경우 인지 확인한다.
	for (int i = 1; i <= n; ++i) {
		int node = i + offset;
		int notNode = -i + offset;
		if (belong[node] == belong[notNode]) {
			cout << 0;
			return 0;
		}
	}
	cout << 1 << "\n";

	// 해를 구한다.

	// 출력한다.
	for (int i = 1; i <= n; ++i) {
		int node = i + offset;
		int notNode = -i + offset;
		cout << (belong[node] < belong[notNode]) << " ";
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

	if (parent == visit[node]) {
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
