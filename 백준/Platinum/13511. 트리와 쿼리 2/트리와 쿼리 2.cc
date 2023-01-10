#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long
#define pll pair<ll,ll>
#define MAXN 100'001
#define MAXE 20

int n, m;
array<vector<pll>, MAXN> edges;
array<ll, MAXN> depth;
array<array<ll, MAXE>, MAXN> parents;
array<array<ll, MAXE>, MAXN> costs;
array<bool, MAXN> visit;

void Setting(int node, int parent, ll cost);
pll GetParentAndCost(int x, int up);
pll GetLCAAndCost(int u, int v);
int GetBetween(int u, int v, int k);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	for (int i = 0; i < n - 1; ++i) {
		ll u, v, w;
		cin >> u >> v >> w;
		edges[u].emplace_back(w, v);
		edges[v].emplace_back(w, u);
	}

	//문제해결
	Setting(1, 0, 0);

	cin >> m;
	int cmd, u, v, k;
	for (int i = 0; i < m; ++i) {
		cin >> cmd;
		if (cmd == 1) {
			cin >> u >> v;
			cout << GetLCAAndCost(u, v).second << "\n";
		}
		else if (cmd == 2) {
			cin >> u >> v >> k;
			cout << GetBetween(u, v, k) << "\n";
		}
	}

	//출력

}

void Setting(int node, int parent, ll cost) {
	visit[node] = true;
	depth[node] = depth[parent] + 1;
	parents[node][0] = parent;
	costs[node][0] = cost;
	for (int i = 1; i < MAXE; ++i) {
		parents[node][i] = parents[ parents[node][i - 1] ][i - 1];
		costs[node][i] = costs[ parents[node][i - 1] ][i - 1] + costs[node][i - 1];
	}

	for (auto[dist, nextNode] : edges[node]) {
		if (!visit[nextNode]) {
			Setting(nextNode, node, dist);
		}
	}
}

pll GetParentAndCost(int x, int up) {	// x의 up번째 부모와 비용을 리턴한다.
	ll cost = 0;
	for (int i = MAXE - 1; i >= 0; --i) {
		if ((1 << i) <= up) {
			up -= (1 << i);
			cost += costs[x][i];
			x = parents[x][i];
		}
	}
	return make_pair(x, cost);
}

pll GetLCAAndCost(int u, int v) {
	if (depth[u] < depth[v])
		swap(u, v);

	ll cost = 0;

	// u를 v와 같은 깊이까지 끌어올린다.
	int diff = depth[u] - depth[v];
	tie(u, cost) = GetParentAndCost(u, diff);
	if (u == v)
		return make_pair(u, cost);

	// u와 v의 공통 부모를 찾는다.
	for (int i = MAXE - 1; i >= 0; --i) {
		if (parents[u][i] != parents[v][i]) {
			cost += costs[u][i] + costs[v][i];
			u = parents[u][i];
			v = parents[v][i];
		}
	}
	cost += costs[u][0] + costs[v][0];
	u = parents[u][0];
	v = parents[v][0];

	return make_pair(u, cost);
}

int GetBetween(int u, int v, int k) {
	--k;
	int lca = GetLCAAndCost(u, v).first;
	int uDiff = depth[u] - depth[lca];
	if (k <= uDiff) {
		return GetParentAndCost(u, k).first;
	}
	else {
		int vDiff = depth[v] - depth[lca];
		vDiff -= k - uDiff;
		return GetParentAndCost(v, vDiff).first;
	}
}
