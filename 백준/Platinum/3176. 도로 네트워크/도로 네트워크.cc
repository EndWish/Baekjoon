#include <iostream>
#include <vector>
#include <tuple>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXN 100'001
#define MAXE 20
#define pii pair<int,int>

using namespace std;

int n, k;
vector<pii> edge[MAXN];	// edge[a] = {c, b} : a에서 b로 c의 거리로 연결됨
int depth[MAXN];
tuple<int,int,int> parent[MAXN][MAXE];	// parent[a][i] = a의 2^i번째 조상이 누구인지, 최소값과 최댓값

void DFS(int node, int prev, int dist);
pii LCM(int a, int b);

int main() 
{

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	int a, b, c;
	for (int i = 0; i < n - 1; ++i) {
		cin >> a >> b >> c;
		edge[a].emplace_back(c, b);
		edge[b].emplace_back(c, a);
	}

	//문제해결
	DFS(1, 0, 0);

	cin >> k;
	for (int i = 0; i < k; ++i) {
		cin >> a >> b;
		auto [minDist, maxDist] = LCM(a, b);
		cout << minDist << " " << maxDist << "\n";
	}

	//출력

}

void DFS(int node, int prev, int dist) {
	depth[node] = depth[prev] + 1;
	parent[node][0] = { prev, dist , dist };
	for (int i = 1; i < MAXE; ++i) {
		auto[subAncestor, subAncestorMinDist, subAncestorMaxDist] = parent[node][i - 1];	// 현재 노드에서 중간조상 까지의 정보
		auto[ancestor, ancestorMinDist, ancestorMaxDist] = parent[subAncestor][i - 1];	// 중간조상부터 조상까지의 정보
		parent[node][i] = { ancestor, min(subAncestorMinDist, ancestorMinDist), max(subAncestorMaxDist,ancestorMaxDist) };
	}

	for (auto [cost, nextNode] : edge[node]) {
		if (nextNode != get<0>(parent[node][0])) {	// 부모가 아닐 경우
			DFS(nextNode, node, cost);
		}
	}
}

pii LCM(int a, int b) {
	if (depth[a] < depth[b]) {	// a가 더 깊은노드가 되도록 한다.
		swap(a, b);
	}

	int resMinDist = numeric_limits<int>::max();
	int resMaxDist = numeric_limits<int>::min();

	// a를 b와 같은 깊이까지 끌어올린다.
	for (int i = MAXE - 1; i >= 0; --i) {
		if (depth[a] - (1 << i) >= depth[b]) {
			auto [ancestor, minDist, maxDist] = parent[a][i];
			a = ancestor;
			resMinDist = min(resMinDist, minDist);
			resMaxDist = max(resMaxDist, maxDist);
		}
	}

	// a와 b가 같을 경우 종료
	if (a == b) {
		return { resMinDist , resMaxDist };
	}

	// a와 b를 공통조상 직전까지 끌어올린다.
	for (int i = MAXE - 1; i >= 0; --i) {
		auto [aAncestor, aMinDist, aMaxDist] = parent[a][i];
		auto [bAncestor, bMinDist, bMaxDist] = parent[b][i];
		if (aAncestor != bAncestor) {
			a = aAncestor;
			b = bAncestor;
			resMinDist = min({ resMinDist, aMinDist, bMinDist });
			resMaxDist = max({ resMaxDist, aMaxDist, bMaxDist });
		}
	}

	auto [aAncestor, aMinDist, aMaxDist] = parent[a][0];
	auto [bAncestor, bMinDist, bMaxDist] = parent[b][0];
	a = aAncestor;
	b = bAncestor;
	resMinDist = min({ resMinDist, aMinDist, bMinDist });
	resMaxDist = max({ resMaxDist, aMaxDist, bMaxDist });

	return { resMinDist , resMaxDist };
}

