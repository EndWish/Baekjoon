#include <iostream>
#include <array>
#include <vector>
#include <stack>
#include <ranges>
#include <algorithm>
#include <numeric>

#define MAXN 100'001

using namespace std;

int t;

int n;
array<int, MAXN> graph;

array<int, MAXN> id;
int idCnt;

array<bool, MAXN> finished;
stack<int> s;

vector<vector<int>> SCC;

int DFS(int x);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> t;
	while (t-- > 0) {
		//최기화,입력값 받기
		idCnt = 0;
		fill(id.begin() + 1, id.begin() + n + 1, 0);
		fill(finished.begin() + 1, finished.begin() + n + 1, false);
		SCC.clear();

		cin >> n;
		for (int i = 1; i <= n; ++i)
			cin >> graph[i];

		//문제해결
		int ans = 0;

		for (int i = 1; i <= n; ++i)
			if (id[i] == 0)	// 방문하지 않았다면
				DFS(i);

		//출력
		//for (auto& scc : SCC) {
		//	for (int v : scc)
		//		cout << v << " ";
		//	cout << "\n";
		//}

		int sum = 0;
		for (vector<int>& v : SCC)
			sum += v.size();

		cout << n - sum << "\n";

	}
}

int DFS(int x)	// 타잔 알고리즘
{
	id[x] = ++idCnt;
	int parent = id[x];
	s.push(x);

	int y = graph[x];	// 다음 노드
	if (id[y] == 0)	// 방문하지 않았다면
		parent = min(parent, DFS(y));
	else if (!finished[y])	// 방문은 했지만 처리중이라면
		parent = min(parent, id[y]);	// 다음 노드의 

	if (id[x] == parent) {	// 내가 부모라면
		vector<int> scc;
		while (true) {
			int p = s.top();
			s.pop();

			finished[p] = true;
			scc.push_back(p);

			if (p == x)
				break;
		}

		if(scc.size() > 1 || y == x)
			 SCC.push_back(move(scc));
	}

	return parent;
}
