#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <tuple>

using namespace std;

#define MAXN 100000

int n, m, x;

array<vector<int>, MAXN + 1> edgesForward, edgesReverse;
array<bool, MAXN + 1> visit;

int GetNumOfFront(int node, array<vector<int>, MAXN + 1>& edges);
int DFS(int node, array<vector<int>, MAXN + 1>& edges);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m >> x;
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		edgesForward[b].push_back(a);
		edgesReverse[a].push_back(b);
	}

	int front = GetNumOfFront(x, edgesForward);
	int behind = GetNumOfFront(x, edgesReverse);

	cout << front + 1 << " " << n - behind;

}

int GetNumOfFront(int node, array<vector<int>, MAXN + 1>& edges) {
	ranges::fill_n(&visit[0], MAXN + 1, false);
	return DFS(node, edges) - 1;
}

int DFS(int node, array<vector<int>, MAXN + 1>& edges) {
	visit[node] = true;

	int result = 1;
	for (int nextNode : edges[node]) {
		if (!visit[nextNode]) {
			result += DFS(nextNode, edges);
		}
	}
	return result;
}
