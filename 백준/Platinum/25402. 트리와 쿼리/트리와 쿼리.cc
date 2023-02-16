#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXN 250'001
#define ll long long

int n, q, k;

array<vector<int>, MAXN> edges;
array<bool, MAXN> visit;
array<bool, MAXN> s;
vector<int> start;

ll DFS(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		cin >> u >> v;
		edges[u].push_back(v);
		edges[v].push_back(u);
	}
	cin >> q;

	//문제해결
	for (int i = 0; i < q; ++i) {
		//fill_n(&s[0], MAXN, false);
		//fill_n(&visit[0], MAXN, false);
		start.clear();

		cin >> k;
		for (int j = 0; j < k; ++j) {
			int node;
			cin >> node;
			s[node] = true;
			start.push_back(node);
		}

		ll ans = 0;
		for (int node : start) {
			if (s[node] && !visit[node]) {
				ll nMember = DFS(node);
				ans += nMember * (nMember - 1) / 2;
			}
		}
		cout << ans << "\n";

		// 초기화
		for (int node : start) {
			visit[node] = false;
			s[node] = false;
		}

	}

}

ll DFS(int node) {
	visit[node] = true;
	int result = 1;
	for (int nextNode : edges[node]) {
		if (s[nextNode] && !visit[nextNode]) {
			result += DFS(nextNode);
		}
	}
	return result;
}
