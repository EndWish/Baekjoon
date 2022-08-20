#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXN 10'001
#define INF numeric_limits<int>::max()

using namespace std;

int v, e;
array<vector<int>, MAXN> edge;
array<int, MAXN> depth;
array<int, MAXN> ladder;
vector<int> ans;

void DFS(int rootNood, int node, int d);

int main() 
{

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> v >> e;
	int a, b;
	for (int i = 0; i < e; ++i) {
		cin >> a >> b;
		edge[a].push_back(b);
		edge[b].push_back(a);
	}

	ladder.fill(INF);

	//문제해결
	for (int i = 1; i <= v; ++i) {
		DFS(i, i, 1);	// depth는 1부터 시작한다. (depth가 0이면 아직 방문하지 않은 것으로 본다.)
	}

	//출력
	ranges::sort(ans);
	cout << ans.size() << "\n";
	for (int value : ans) {
		cout << value << " ";
	}

}

void DFS(int rootNood, int node, int d) {
	depth[node] = d;

	bool isArticulationPoint = false;
	for (int i = 0; i < edge[node].size(); ++i) {
		int y = edge[node][i];
		if (depth[y] == 0) {	// 아직 방문을 하지 않은 노드일 경우
			DFS(rootNood, y, d + 1);	// 자식 노드에게 깊이값 부여
			ladder[node] = min(ladder[node], ladder[y]);	// 자신을 포함한 서브트리중에 가장 높이 올라갈 수 있는 높이 저장 (자식들중에 연결된 곳의 깊이확인)
			if (ladder[y] >= depth[node]) {	// 자신의 서브트리가 최대로 올라갈 수 있는 곳이 자신or자신보다 낮은 위치(더 깊은곳)일 경우 자신은 단절점이 된다.
				isArticulationPoint = true;
			}
		}
		else {	// 이미 방문한 노드
			if (depth[y] < depth[node]) {	// 조상일 경우
				ladder[node] = min(ladder[node], depth[y]);		// 자신을 포함한 서브트리중에 가장 높이 올라갈 수 있는 높이 저장 (자신과 연결된 부분의 깊이 확인)
			}
		}
	}

	if (node == rootNood) {	// root노드일 경우
		isArticulationPoint = false;
		int nChildren = 0;
		for (int i = 0; i < edge[node].size(); ++i) {
			int y = edge[node][i];
			if (depth[y] == 2) {	// 자식일 경우
				if (++nChildren >= 2) {	// 자식의 수++, 자식이 2명이상이면 단절점이다.
					isArticulationPoint = true;
					break;
				}
			}
		}
	}

	if (isArticulationPoint) {
		ans.push_back(node);
	}
}
