#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n;

array<vector<int>, 52> edges;
array<array<int, 52>, 52> capacity, flow;
array<int, 52> prevNode;

int NetworkFlow();
int NameToIndex(char ch);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	
	for (int i = 0; i < n; ++i) {
		char ch1, ch2;
		int inputCapacity;
		cin >> ch1 >> ch2 >> inputCapacity;
		int node1 = NameToIndex(ch1), node2 = NameToIndex(ch2);
		edges[node1].push_back(node2);
		edges[node2].push_back(node1);
		capacity[node1][node2] += inputCapacity;
		capacity[node2][node1] += inputCapacity;
	}

	cout << NetworkFlow();
	
}

int NetworkFlow() {

	int result = 0;

	while (true) {

		fill_n(&prevNode[0], 52, -1);

		// BFS를 수행하여 흐를 수 있는 경로를 찾는다.
		int startNode = NameToIndex('A');
		int endNode = NameToIndex('Z');
		queue<int> q;
		q.push(startNode);
		prevNode[startNode] = startNode;
		while (!q.empty()) {
			int node = q.front();
			q.pop();

			for (int nextNode : edges[node]) {
				if (prevNode[nextNode] == -1 && flow[node][nextNode] < capacity[node][nextNode]) {
					prevNode[nextNode] = node;
					q.push(nextNode);
				}
			}
		}

		// 더이상 경로가 없을 경우 반복문을 빠져나온다.
		if (prevNode[endNode] == -1)
			break;

		// 최대 흘릴 수 있는 양을 구한다.
		int maxFlow = numeric_limits<int>::max();
		for (int node = endNode; node != startNode; node = prevNode[node]) {
			int preNode = prevNode[node];
			maxFlow = min(maxFlow, capacity[preNode][node] - flow[preNode][node]);
		}

		// 물을 흘려 보낸다.
		for (int node = endNode; node != startNode; node = prevNode[node]) {
			int preNode = prevNode[node];
			flow[preNode][node] += maxFlow;
			flow[node][preNode] -= maxFlow;
		}

		// 추가적으로 흘려보낸 양을 결과에 더한다.
		result += maxFlow;
	}
	return result;
}

int NameToIndex(char ch) {
	if (isupper(ch))
		return ch - 'A';
	else
		return ch - 'a' + 26;
}

