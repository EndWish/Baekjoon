#include <iostream>
#include <array>
#include <queue>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define MAXN 1000
#define ll long long
#define tu tuple<int,int,int>
#define pii pair<int,int>

int n;
array<array<int, MAXN>, MAXN> edges;

ll Prim(int start);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	//초기화
	cin >> n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> edges[i][j];

	//문제해결
	cout << Prim(0);

	//출력

}

ll Prim(int start) {
	ll ans = 0;
	array<bool, MAXN> finished;
	finished.fill(false);
	priority_queue<tu> pq;
	pq.emplace(-0, start, start);

	while (!pq.empty()) {
		auto [cost, node, preNode] = pq.top();
		cost *= -1;
		pq.pop();

		if (finished[node])
			continue;

		finished[node] = true;
		ans += cost;

		for (int nextNode = 0; nextNode < n; ++nextNode) {
			if (!finished[nextNode]) {

				pq.emplace(-edges[node][nextNode], nextNode, node);
			}
		}
	}

	return ans;
}
