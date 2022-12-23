#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>
#include <array>
#include <queue>

using namespace std;

#define MAXN 1001
#define pii pair<int,int>

int n, m;
array<char, MAXN> sex;
array<bool, MAXN> finished;
array<vector<pii>, MAXN> edges;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> sex[i];
	}
	for (int i = 1; i <= m; ++i) {
		int u, v, d;
		cin >> u >> v >> d;
		if (sex[u] != sex[v]) {
			edges[u].emplace_back(d, v);
			edges[v].emplace_back(d, u);
		}
	}
	
	//문제해결
	int sum = 0;
	int finishedCount = 0;
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	pq.emplace(0, 1);
	while (!pq.empty()) {
		auto [dist, node] = pq.top();
		pq.pop();

		if (finished[node])
			continue;
		finished[node] = true;

		++finishedCount;
		sum += dist;

		for (auto edge : edges[node]) {
			pq.push(edge);
		}
	}

	//출력
	if (finishedCount == n) {
		cout << sum;
	}
	else {
		cout << -1;
	}

}
