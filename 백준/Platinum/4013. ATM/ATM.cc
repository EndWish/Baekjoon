#include <iostream>
#include <vector>
#include <stack>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>

using namespace std;

#define MAXN 500'001

struct SCC {
	int money = 0;
	bool restaurant = false;
};

int n, m, s, p;
array<vector<int>, MAXN> edges;
array<int, MAXN> money;
array<int, MAXN> restaurants;
array<int, MAXN> belong;
array<int, MAXN> visit;
int idCount;
stack<int> st;

vector<SCC> SCCs;
vector<int> dp;
vector<unordered_set<int>> SCCedges;	// 도착지에서 출발지로가는 간선이다.

int DFS(int node);
int DP(int SCCnode);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	visit.fill(-1);
	belong.fill(-1);

	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		edges[u].push_back(v);
	}
	for (int i = 1; i <= n; ++i)
		cin >> money[i];

	cin >> s >> p;
	for (int i = 0; i < p; ++i) {
		int num;
		cin >> num;
		restaurants[num] = true;
	}

	//문제해결
	for (int i = 1; i <= n; ++i) {
		if(visit[i] == -1)
			DFS(i);
	}
	
	for (int start = 1; start <= n; ++start) {
		for (int end : edges[start]) {
			if (belong[start] != belong[end])
				SCCedges[belong[end]].insert(belong[start]);
		}
	}

	int ans = 0;
	for (int i = 0; i < SCCs.size(); ++i) {
		if(SCCs[i].restaurant)
			ans = max(ans, DP(i));
	}

	cout << ans;
}

int DFS(int node) {
	visit[node] = ++idCount;
	st.push(node);

	int parent = visit[node];
	for (int nextNode : edges[node]) {
		if (visit[nextNode] == -1)
			parent = min(parent, DFS(nextNode));
		else if (belong[nextNode] == -1)
			parent = min(parent, visit[nextNode]);
	}

	if (parent == visit[node]) {
		SCC scc;
		while (true) {
			int x = st.top();
			st.pop();
			scc.money += money[x];
			if (restaurants[x])
				scc.restaurant = true;
			belong[x] = SCCs.size();
			if (node == x)
				break;
		}
		SCCs.push_back(scc);
		dp.push_back(-1);
		SCCedges.push_back({});
	}

	return parent;
}

int DP(int SCCnode) {
	if (dp[SCCnode] != -1)
		return dp[SCCnode];

	if (SCCnode == belong[s])
		dp[SCCnode] = SCCs[SCCnode].money;
	else
		dp[SCCnode] = -2;

	for (int preSCCnode : SCCedges[SCCnode]) {
		if (DP(preSCCnode) == -2)
			continue;
		dp[SCCnode] = max(dp[SCCnode], DP(preSCCnode) + SCCs[SCCnode].money);
	}
	return dp[SCCnode];
}
