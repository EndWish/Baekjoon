#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

struct Edge {
	int cost;
	int node1, node2;

	Edge(int a, int b, int c) : cost(c), node1(a), node2(b) {

	}
};

int n, m;
vector<Edge> edges;
array<int, 1001> parent;

int Find(int x);
void Unite(int a, int b);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	iota(parent.begin(), parent.end(), 0);

	cin >> n >> m;
	int a, b, c;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> c;
		edges.emplace_back(a, b, c);
	}

	//문제해결
	int ans = 0;
	ranges::sort(edges, {}, &Edge::cost);
	for (int i = 0; i < edges.size(); ++i) {
		if (Find(edges[i].node1) != Find(edges[i].node2)) {	// 연결해도 사이클이 발생하지 않는다.
			Unite(edges[i].node1, edges[i].node2);
			ans += edges[i].cost;
		}
	}

	//출력
	cout << ans;

}

int Find(int x) {
	if (x == parent[x])
		return x;
	return parent[x] = Find(parent[x]);
}

void Unite(int a, int b) {
	a = Find(a);
	b = Find(b);
	if (a < b)
		parent[b] = a;
	else
		parent[a] = b;
}
