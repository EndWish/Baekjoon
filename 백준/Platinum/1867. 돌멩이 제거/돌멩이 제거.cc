#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXN 501

int n, k;
array<vector<int>, MAXN> edges;
array<int, MAXN> visit;
array<bool, MAXN> finished;

int BipartiteMatching();
bool DFS(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	ranges::fill(visit, -1);

	cin >> n >> k;
	for (int i = 0; i < k; ++i) {
		int r, c;
		cin >> r >> c;
		edges[r].push_back(c);
	}
	
	//문제해결
	cout << BipartiteMatching();

}

int BipartiteMatching() {
	int result = 0;
	for (int i = 1; i <= n; ++i) {
		ranges::fill(finished, false);
		if (DFS(i))
			++result;
	}
	return result;
}

bool DFS(int node) {
	for (int otherNode : edges[node]) {
		if (visit[otherNode] == -1) {
			visit[otherNode] = node;
			return true;
		}
		if (!finished[otherNode]) {
			finished[otherNode] = true;
			if (DFS(visit[otherNode])) {
				visit[otherNode] = node;
				return true;
			}
		}
	}
	return false;
}
