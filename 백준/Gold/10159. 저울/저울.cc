#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXN 101

using namespace std;

int n, m;
vector<int> edgeBigger[MAXN];
vector<int> edgeSmaller[MAXN];
bool visit[MAXN];

int DFS(int node, vector<int>* edge);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	int a, b;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		edgeBigger[b].push_back(a);
		edgeSmaller[a].push_back(b);
	}

	//문제해결
	for (int node = 1; node <= n; ++node) {
		int compareNum =  - 1;
		fill_n(visit, MAXN, false);
		compareNum += DFS(node, edgeBigger);
		fill_n(visit, MAXN, false);
		compareNum += DFS(node, edgeSmaller);
		cout << n - compareNum << "\n";
	}

	//출력
}

int DFS(int node, vector<int>* edge) {
	visit[node] = true;
	int result = 1;

	for (int nextNode : edge[node]) {
		if (!visit[nextNode]) {
			result += DFS(nextNode, edge);
		}
	}

	return result;
}
