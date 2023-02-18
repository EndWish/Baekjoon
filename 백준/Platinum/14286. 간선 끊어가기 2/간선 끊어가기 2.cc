#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXN 501
#define INF numeric_limits<int>::max()
#define pii pair<int,int>

int n, m, s, t;
array<vector<int>, MAXN> edges;
array<array<int, MAXN>, MAXN> flow, capacity;
array<int, MAXN> visit;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		edges[a].push_back(b);
		edges[b].push_back(a);
		capacity[a][b] = c;
		capacity[b][a] = c;
	}
	cin >> s >> t;
	
	//문제해결
	int totalFlow = 0;
	while (true) {
		fill_n(&visit[0], MAXN, -1);
		queue<int> q;
		q.push(s);
		visit[s] = s;
		while (!q.empty()) {
			int node = q.front();
			q.pop();

			if (node == t)
				break;

			for (int nextNode : edges[node]) {
				if (visit[nextNode] == -1 && flow[node][nextNode] < capacity[node][nextNode]) {
					visit[nextNode] = node;
					q.push(nextNode);
				}
			}
		}

		if (visit[t] == -1)
			break;

		int water = INF;
		for (int node = t; node != s; node = visit[node]) {
			int preNode = visit[node];
			water = min(water, capacity[preNode][node] - flow[preNode][node]);
		}
		for (int node = t; node != s; node = visit[node]) {
			int preNode = visit[node];
			flow[preNode][node] += water;
			flow[node][preNode] -= water;
		}

		totalFlow += water;
	}

	cout << totalFlow;

}
