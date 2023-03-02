#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define OFFSET 400
#define INF numeric_limits<int>::max()

int const source = 0;
int const sink = 801;

int n, m;
array<vector<int>, 802> edges;	// 0 : 소스, 1~400:직원, 401~800:일, 801:싱크
array<array<int, 802>, 802> flow, capacity, costs;

pair<int, int> Edmond_Karp();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	for (int worker = 1; worker <= n; ++worker) {
		edges[source].push_back(worker);
		edges[worker].push_back(source);
		capacity[source][worker] = 1;
		//capacity[worker][source] = 0;

		int nEdge;
		cin >> nEdge;
		while (nEdge-- > 0) {
			int work, cost;
			cin >> work >> cost;
			edges[worker].push_back(work + OFFSET);
			edges[work + OFFSET].push_back(worker);
			capacity[worker][work + OFFSET] = 1;
			//capacity[work + OFFSET][worker] = 0;
			costs[worker][work + OFFSET] = cost;
			costs[work + OFFSET][worker] = -cost;
		}
	}

	for (int work = 1; work <= m; ++work) {
		edges[work + OFFSET].push_back(sink);
		edges[sink].push_back(work + OFFSET);
		capacity[work + OFFSET][sink] = 1;
		//capacity[sink][work + OFFSET] = 0;
	}

	//문제해결
	auto [totalFlow, totalCost] = Edmond_Karp();
	cout << totalFlow << "\n";
	cout << totalCost << "\n";
	
}

pair<int,int> Edmond_Karp() {
	array<int, 802> dist;
	array<int, 802> prevNodes;
	array<int, 802> visit;
	array<bool, 802> inq;

	int totalFlow = 0;
	int totalCost = 0;

	while (true) {
		// 가장 비용이 적은 경로를 찾는다.
		dist.fill(INF);
		dist[source] = 0;
		prevNodes.fill(-1);
		visit.fill(0);
		inq.fill(false);

		queue<int> q;
		q.push(source);
		++visit[source];
		inq[source] = true;
		while (!q.empty()) {
			int node = q.front();
			q.pop();
			inq[node] = false; 

			if (visit[node] == 802)
				cout << "음수 사이클\n";

			for (int nextNode : edges[node]) {
				// 비용이 절감되고 흘려보낼 수 있을 경우
				if (dist[node] + costs[node][nextNode] < dist[nextNode] && flow[node][nextNode] < capacity[node][nextNode]) {
					dist[nextNode] = dist[node] + costs[node][nextNode];
					prevNodes[nextNode] = node;
					if (!inq[nextNode]) {
						++visit[nextNode];
						q.push(nextNode);
						inq[nextNode] = true;
					}
				}
			}
		}

		// 더이상 경로를 찾을 수 없을 경우 멈춘다.
		if (prevNodes[sink] == -1)
			break;

		// 물을 흘려보낸다.
		for (int node = sink; node != source; node = prevNodes[node]) {
			int prevNode = prevNodes[node];
			++flow[prevNode][node];
			--flow[node][prevNode];
			totalCost += costs[prevNode][node];
		}
		++totalFlow;

	}

	return { totalFlow, totalCost };
}
