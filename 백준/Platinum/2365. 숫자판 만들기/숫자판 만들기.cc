#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define WID 52
#define WID2 (WID*WID)
#define INF numeric_limits<int>::max()

/*	(0,0) == source
	(1,1)~(n,n) == 행렬
	(r, n+1),(n+1, c) == 각 행 또는 각 열의 합을 나타내는 노드
	(n+1,n+1) == sink
*/

int n, source, sink, sum;
array<vector<int>, WID2> edges;
array<array<int, WID2>, WID2> flow, capacity;

void MakeGraph();
void ModifyCapacity(int x);
int GetNode(int r, int c);
int Edmonds_Karp();
int GetMaxValue();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	MakeGraph();
	
	//문제해결
	int s = 0, e = sum;
	while (s < e) {
		int mid = (s + e) / 2;
		ModifyCapacity(mid);
		if (Edmonds_Karp() == sum) {
			e = min(mid, GetMaxValue());
		}
		else {
			s = mid + 1;
		}
	}
	ModifyCapacity(s);
	Edmonds_Karp();

	cout << s << "\n";
	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= n; ++c) {
			int otherNode = GetNode(r, n + 1);
			int node = GetNode(r, c);

			// 행의 합에 연결
			cout << flow[otherNode][node] << " ";
		}
		cout << "\n";
	}


}

void MakeGraph() {
	cin >> n;
	source = GetNode(0, 0);
	sink = GetNode(n + 1, n + 1);

	// 행의 합 입력받기
	for (int r = 1; r <= n; ++r) {
		int num;
		cin >> num;
		int node = GetNode(r, n + 1);
		edges[source].push_back(node);
		edges[node].push_back(source);
		capacity[source][node] = num;
		sum += num;
	}

	// 열의 합 입력받기
	for (int c = 1; c <= n; ++c) {
		int num;
		cin >> num;
		int node = GetNode(n + 1, c);
		edges[node].push_back(sink);
		edges[sink].push_back(node);
		capacity[node][sink] = num;
	}

	// 모든 행렬의 간선 만들기
	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= n; ++c) {
			int node = GetNode(r, c);
			int otherNode;

			// 행의 합에 연결
			otherNode = GetNode(r, n + 1);
			edges[otherNode].push_back(node);
			edges[node].push_back(otherNode);
			capacity[otherNode][node] = sum;

			// 열의 합에 연결
			otherNode = GetNode(n + 1, c);
			edges[node].push_back(otherNode);
			edges[otherNode].push_back(node);
			capacity[node][otherNode] = INF;

		}
	}
}
void ModifyCapacity(int x) {
	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= n; ++c) {
			// 시작점에서 출발하는 간선
			int node = GetNode(r, c);
			int otherNode = GetNode(r, n + 1);

			// 행의 합에 연결
			capacity[otherNode][node] = x;
		}
	}
}
int GetNode(int r, int c) {
	return c + r * WID;
}

int Edmonds_Karp() {
	int totalFlow = 0;

	fill_n(&flow[0][0], WID2 * WID2, 0);
	vector<int> visit(WID2, -1);

	while (true) {
		ranges::fill(visit, -1);

		queue<int> q;
		q.push(source);
		visit[source] = source;
		while (!q.empty()) {
			int node = q.front();
			q.pop();

			if (node == sink)
				break;

			for (int nextNode : edges[node]) {
				if (visit[nextNode] == -1 && flow[node][nextNode] < capacity[node][nextNode]) {
					visit[nextNode] = node;
					q.push(nextNode);
				}
			}
		}

		// 더이상 경로가 없을 경우
		if (visit[sink] == -1)
			break;

		int water = INF;
		for (int node = sink; node != source; node = visit[node]) {
			int preNode = visit[node];
			water = min(water, capacity[preNode][node] - flow[preNode][node]);
		}
		for (int node = sink; node != source; node = visit[node]) {
			int preNode = visit[node];
			flow[preNode][node] += water;
			flow[node][preNode] -= water;
		}
		totalFlow += water;
	}


	return totalFlow;
}
int GetMaxValue() {
	int result = 0;
	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= n; ++c) {
			int otherNode = GetNode(r, n + 1);
			int node = GetNode(r, c);

			result = max(result, flow[otherNode][node]);
		}
	}
	return result;
}
