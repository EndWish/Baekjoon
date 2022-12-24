#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>
#include <array>
#include <deque>
#include <numeric>

using namespace std;

#define MAXN 251
#define INF numeric_limits<int>::max()
#define pii pair<int,int>

int n, m, k;
array<array<int, MAXN>, MAXN> edges;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	fill_n(&edges[0][0], MAXN * MAXN, INF);
	for (int i = 0; i < MAXN; ++i)
		edges[i][i] = 0;

	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int u, v, b;
		cin >> u >> v >> b;
		edges[u][v] = 0;
		if (b == 0) {
			edges[v][u] = 1;
		}
		else {
			edges[v][u] = 0;
		}
	}
	
	//문제해결
	for (int via = 1; via <= n; ++via) {
		for (int s = 1; s <= n; ++s) {
			if (via == s)
				continue;
			for (int e = 1; e <= n; ++e) {
				if (s == e || via == e)
					continue;
				if (edges[s][via] == INF || edges[via][e] == INF)
					continue;

				edges[s][e] = min(edges[s][e], edges[s][via] + edges[via][e]);
			}
		}
	}

	//출력
	cin >> k;
	for (int i = 0; i < k; ++i) {
		int s, e;
		cin >> s >> e;
		cout << edges[s][e] << "\n";

	}

}
