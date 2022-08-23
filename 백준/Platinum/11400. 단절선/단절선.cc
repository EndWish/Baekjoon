#include <iostream>
#include <vector>
#include <span>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXV 100'001
#define INF numeric_limits<int>::max()
#define pii pair<int,int>

using namespace std;

int v, e;
vector<int> edge[MAXV];
int depth[MAXV];
int ladder[MAXV];
vector<pii> ans;

void DFS(int node, int prev);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> v >> e;
	int a, b;
	for (int i = 0; i < e; ++i) {
		cin >> a >> b;
		edge[a].push_back(b);
		edge[b].push_back(a);
	}

	//문제해결
	DFS(1, 1);
	ranges::sort(ans);

	//출력
	cout << ans.size() << "\n";
	for (auto [u, v] : ans) {
		cout << u << " " << v << "\n";
	}

}

void DFS(int node, int prev) {
	depth[node] = depth[prev] + 1;
	ladder[node] = depth[node];

	for (int nextNode : edge[node]) {
		if (depth[nextNode] == 0) {	//아직 방문을 하지 않은 곳일 경우
			DFS(nextNode, node);
			ladder[node] = min(ladder[node], ladder[nextNode]);
			// 자식노드가 최대로 올라갈 수 있는 곳이 나보다 (낮은 곳)깊은곳일때 그 자식과 연결된 간선이 단절선이다. 
			if (ladder[nextNode] > depth[node]) {
				if(node < nextNode)
					ans.emplace_back(node, nextNode);
				else
					ans.emplace_back(nextNode, node);
			}
		}
		else {
			if (depth[node] > depth[nextNode] && nextNode != prev) {	// 조상 노드일 경우
				ladder[node] = min(ladder[node], depth[nextNode]);
			}
		}
	}

}
