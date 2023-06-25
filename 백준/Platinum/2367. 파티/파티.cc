#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <queue>

using namespace std;

#define MAXN 200
#define MAXD 100
#define MAX_NODE (2 + MAXN + MAXD)

int n, k, d;
int source, sink;
array<vector<int>, MAX_NODE> edges;
array<array<int, MAX_NODE>, MAX_NODE> flow, capacity;

int NetworkFlow();

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	// 0 : 소스, 1~n : 사람, n + 1 ~ n + d : 음식, n + d + 1 : 싱크
	cin >> n >> k >> d;
	source = 0;
	sink = n + d + 1;
	
	// 소스와 사람을 연결한다.
	for (int i = 1; i <= n; ++i) {
		edges[0].push_back(i);
		//edges[i].push_back(0);
		capacity[0][i] = k;
	}

	// 음식과 싱크를 연결한다.
	for (int food = 1; food <= d; ++food) {
		int input;
		cin >> input;
		edges[n + food].push_back(sink);
		//edges[sink].push_back(n + i);
		capacity[n + food][sink] = input;
	}

	// 사람과 음식을 연결한다
	for (int person = 1; person <= n; ++person) {
		int nFood;
		cin >> nFood;
		for (int j = 0; j < nFood; ++j) {
			int food;
			cin >> food;
			edges[person].push_back(food + n);
			edges[food + n].push_back(person);
			capacity[person][food + n] = 1;
		}
	}

	cout << NetworkFlow();

}

int NetworkFlow() {

	vector<int> visit(MAX_NODE, -1);
	int result = 0;

	// 흐를 수 있는 경로가 없을때 까지 물을 흘려준다.
	while (true) {
		ranges::fill(visit, -1);

		queue<int> q;
		q.push(source);
		visit[source] = source;

		while (!q.empty()) {
			int node = q.front();
			q.pop();

			for (int nextNode : edges[node]) {
				// 이미 방문했으면 건너뛴다.
				if (visit[nextNode] != -1)
					continue;

				// 이미 최대치로 흐르고 있을 경우 건너 뛴다.
				if (flow[node][nextNode] == capacity[node][nextNode])
					continue;

				// 다음 노드로 흐를 수 있을 경우
				q.push(nextNode);
				visit[nextNode] = node;
			}
		}

		// 흐를 수 있는 경로가 없을 경우
		if (visit[sink] == -1) {
			break;
		}

		// 찾아낸 경로로 흘릴 수 있는 최대량을 찾는다.
		int water = numeric_limits<int>::max();
		for (int node = sink; node != source; node = visit[node]) {
			int preNode = visit[node];
			water = min(water, capacity[preNode][node] - flow[preNode][node]);
		}

		// 물을 흘린다.
		for (int node = sink; node != source; node = visit[node]) {
			int preNode = visit[node];
			flow[preNode][node] += water;
			flow[node][preNode] -= water;
		}
		result += water;
	}

	return result;
}
