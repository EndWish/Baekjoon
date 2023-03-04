#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

// 0 : source, 1 ~ 400 : worker, 401 ~ 800 : work, 801 : sink
#define pii pair<int,int>
#define MAXN 802
#define INF numeric_limits<int>::max()
int const source = 0;
int const sink = 801;
int const offset = 400;

int n, m;
array<vector<int>, MAXN> edges;
array<array<int, MAXN>, MAXN> costs, flow, capacity;

void MakeGraph();
pii EdmondKarp();
void SPFA(int startNode, array<int, MAXN>& preNode);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	MakeGraph();

	//문제해결
	auto [totalFlow, totalCost] = EdmondKarp();
	cout << totalFlow << "\n";
	cout << totalCost << "\n";
	
}

void MakeGraph() {
	cin >> n >> m;
	int nWork, work, cost;
	for (int worker = 1; worker <= n; ++worker) {
		// 소스와 직원을 연결한다.
		edges[source].push_back(worker);
		edges[worker].push_back(source);
		capacity[source][worker] = 1;

		cin >> nWork;
		for (int j = 0; j < nWork; ++j) {
			// 직원과 일을 연결한다.
			cin >> work >> cost;
			edges[worker].push_back(work + offset);
			edges[work + offset].push_back(worker);
			capacity[worker][work + offset] = 1;
			costs[worker][work + offset] = cost;	
			costs[work + offset][worker] = -cost;
		}
	}
	for (int work = 1; work <= m; ++work) {
		// 일과 싱크를 연결한다.
		edges[work + offset].push_back(sink);
		edges[sink].push_back(work + offset);
		capacity[work + offset][sink] = 1;
	}
}

pii EdmondKarp() {
	int totalFlow = 0, totalCost = 0;
	array<int, MAXN> preNodes;

	while (true) {
		// SPFA을 사용하여 경로를 찾는다.
		SPFA(source, preNodes);

		// 더이상 경로가 없으면 그만한다.
		if (preNodes[sink] == -1)
			break;

		// 해당경로로 물을 흘려준다. <path관련된 것들을 주석해제하면 경로를 출력해준다.>
		
		//vector<int> path;
		for (int node = sink; node != source; node = preNodes[node]) {
			//path.push_back(node);
			int preNode = preNodes[node];
			++flow[preNode][node];
			--flow[node][preNode];
			totalCost += costs[preNode][node];
		}
		//path.push_back(source);
		++totalFlow;

		//ranges::reverse(path);
		//cout << source << " ";
		//for (int i = 0; i < path.size() - 1; ++i) {
		//	int node = path[i];
		//	int nextNode = path[i + 1];
		//	cout << " --(" << costs[node][nextNode] << ")--> " << nextNode << " ";
		//}
		//cout << "\n";

	}

	return { totalFlow, totalCost };
}

void SPFA(int startNode, array<int, MAXN>& preNode) {
	// 초기화
	array<int, MAXN> visit;
	array<bool, MAXN> inQ;
	array<int, MAXN> dist;
	visit.fill(0);
	inQ.fill(false);
	preNode.fill(-1);
	dist.fill(-INF);
	dist[startNode] = 0;

	// 시작 노드 삽입
	queue<int> q;
	q.push(startNode);
	++visit[startNode];
	inQ[startNode] = true;

	// SPFA
	while (!q.empty()) {
		int node = q.front();
		q.pop();
		inQ[node] = false;

		if (MAXN <= visit[node]) {
			cout << "음수 사이클이 존재한다.\n";
			break;
		}

		for (int nextNode : edges[node]) {
			// 경로가 존재하고 더 비싼경우
			if (dist[nextNode] < dist[node] + costs[node][nextNode] && flow[node][nextNode] < capacity[node][nextNode]) {
				dist[nextNode] = dist[node] + costs[node][nextNode];
				preNode[nextNode] = node;
				if (!inQ[nextNode]) {
					inQ[nextNode] = true;
					q.push(nextNode);
					++visit[nextNode];
				}
			}
		}
	}

}
