#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define pii pair<int,int>

int n, m;
array<vector<pii>, 1001> edges;

int MST();
int MSTReverse();

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	// 입력받기
	cin >> n >> m;
	for (int i = 0; i < m + 1; ++i) {
		int u, v, cost;
		cin >> u >> v >> cost;
		edges[u].emplace_back(1 - cost, v);	// 오르막길 : 1, 내리막길 : 0
		edges[v].emplace_back(1 - cost, u);
	}

	cout << MSTReverse() - MST();

}

int MST() {
	array<bool, 1001> visit;
	visit.fill(false);

	priority_queue<pii, vector<pii>, greater<pii>> pq;

	int result = 0;

	pq.emplace(0, 0);
	while (!pq.empty()) {
		auto [dist, node] = pq.top();
		pq.pop();

		if (visit[node])
			continue;
		visit[node] = true;
		if (dist == 1)
			++result;

		for (auto[cost ,nextNode] : edges[node]) {
			if (visit[nextNode])
				continue;

			pq.emplace(cost, nextNode);
		}
	}
	
	return result * result;
}

int MSTReverse() {
	array<bool, 1001> visit;
	visit.fill(false);

	priority_queue<pii, vector<pii>, less<pii>> pq;

	int result = 0;

	pq.emplace(0, 0);
	while (!pq.empty()) {
		auto [dist, node] = pq.top();
		pq.pop();

		if (visit[node])
			continue;
		visit[node] = true;
		if (dist == 1)
			++result;

		for (auto [cost, nextNode] : edges[node]) {
			if (visit[nextNode])
				continue;

			pq.emplace(cost, nextNode);
		}
	}

	return result * result;
}