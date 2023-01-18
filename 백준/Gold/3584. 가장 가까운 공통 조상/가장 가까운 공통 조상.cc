#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>

using namespace std;

#define MAXN 10'001

int t, n, m;
array<int, MAXN> parent;
array<bool, MAXN> visit;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> t;
	while (t-- > 0) {
		//초기화,입력값 받기
		parent.fill(0);
		visit.fill(false);

		cin >> n;
		int u, v;
		for (int i = 0; i < n - 1; ++i) {
			cin >> u >> v;
			parent[v] = u;
		}

		//문제해결
		cin >> u >> v;
		while (u != 0) {
			visit[u] = true;
			u = parent[u];
		}
		while (!visit[v]) {
			v = parent[v];
		}
		cout << v << "\n";

	}


}
