#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
//#include <numeric>
//#include <format>

#define MAXN 401
#define MAXE 10

using namespace std;

int n, k, s;
vector<int> asendingEdge[MAXN];
vector<int> desendingEdge[MAXN];
bool visit[MAXN];

int Comp(int a, int b);
bool DFS(int node, vector<int>* edge, int targetNode);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> k;
	int a, b;
	for (int i = 0; i < k; ++i) {
		cin >> a >> b;
		asendingEdge[a].push_back(b);
		desendingEdge[b].push_back(a);
	}

	//문제해결
	cin >> s;
	for (int i = 0; i < s; ++i) {
		cin >> a >> b;
		cout << Comp(a, b) << "\n";
	}

	//출력

}

int Comp(int a, int b) {
	fill_n(visit, MAXN, false);
	if (DFS(a, asendingEdge, b))
		return -1;
	if (DFS(a, desendingEdge, b))
		return 1;
	return 0;
}

bool DFS(int node, vector<int>* edge, int targetNode) {
	visit[node] = true;
	for (int nextNode : edge[node]) {
		if (nextNode == targetNode)
			return true;

		if (!visit[nextNode] && DFS(nextNode, edge, targetNode))
			return true;
	}
	return false;
}
