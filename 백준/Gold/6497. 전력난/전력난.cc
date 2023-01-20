#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>

using namespace std;

#define pii pair<int,int>
#define MAXM 200'000

int m, n;
array<vector<pii>, MAXM> edges;
array<bool, MAXM> finished;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	while (true) {
		//초기화,입력값 받기
		edges.fill({});
		finished.fill(false);

		cin >> m >> n;
		if (m == 0 && n == 0)
			break;

		int maxSum = 0;
		for (int i = 0; i < n; ++i) {
			int x, y, z;
			cin >> x >> y >> z;
			maxSum += z;
			edges[x].emplace_back(z, y);
			edges[y].emplace_back(z, x);
		}

		//문제해결
		int sum = 0;
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		pq.emplace(0, 0);
		while (!pq.empty()) {
			auto [dist, node] = pq.top();
			pq.pop();

			if (finished[node])
				continue;
			finished[node] = true;
			sum += dist;
			//cout << node << "확정 " << "거리 : " << dist << "\n";

			for (auto [nextDist, nextNode] : edges[node]) {
				if (!finished[nextNode]) {
					pq.emplace(nextDist, nextNode);
				}
			}
		}

		cout << maxSum - sum << "\n";

	}

}

