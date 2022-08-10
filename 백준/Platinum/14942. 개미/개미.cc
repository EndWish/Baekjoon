#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXN 500'001
#define MAXE 20
#define pii pair<int,int>

using namespace std;

int n;
vector<int> energy;
array<vector<pii>, MAXN> edge;
array<array<pii, MAXE>, MAXN> parent;	// 거리, 노드

void DFS(int node, int prev, int dist);

int main() 
{

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	energy.assign(n + 1, 0);

	for (int& e : energy | views::drop(1))
		cin >> e;

	int a, b, c;
	for (int i = 1; i <= n - 1; ++i) {
		cin >> a >> b >> c;
		edge[a].emplace_back(c, b);	// 길이, 다음노드
		edge[b].emplace_back(c, a);	// 길이, 다음노드
	}

	//문제해결
	DFS(1, 1, 0);
	for (int i = 1; i <= 4; ++i) {
		for (int j = 0; j < 10; ++j) {
		}
	}

	for (int i = 1; i <= n; ++i) {
		int node = i;
		int e = energy[i];
		for (int i = MAXE - 1; i >= 0; --i) {
			if (e >= parent[node][i].first) {
				e -= parent[node][i].first;
				node = parent[node][i].second;
				
				if (node == 0 || node == 1) {
					node = 1;
					break;
				}
			}
		}
		cout << node <<"\n";
	}

	//출력

	
}

void DFS(int node, int prev, int dist) {
	parent[node][0] = { dist , prev };
	for (int i = 1; i < MAXE; ++i) {
		int subAncestor = parent[node][i - 1].second;
		int ancestorDist = parent[node][i - 1].first + parent[subAncestor][i - 1].first;
		int ancestor = parent[subAncestor][i - 1].second;
		parent[node][i] = { ancestorDist , ancestor };
	}

	for (auto [cost, nextNode] : edge[node]) {
		if(nextNode != prev)
			DFS(nextNode, node, cost);
	}

}
