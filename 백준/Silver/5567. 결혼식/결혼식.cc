#include <iostream>
#include <queue>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define MAXN 501

int n, m;
vector<int> edges[MAXN];
array<int, MAXN> visit;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	visit.fill(-1);
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		edges[u].push_back(v);
		edges[v].push_back(u);
	}

	//문제해결
	int ans = 0;

	queue<int> q;
	q.push(1);
	visit[1] = 0;
	while (!q.empty()) {
		int x = q.front();
		q.pop();

		if (2 <= visit[x])
			continue;

		for (int i = 0; i < edges[x].size(); ++i) {
			int y = edges[x][i];
			if (visit[y] == -1) {
				visit[y] = visit[x] + 1;
				q.push(y);
				++ans;
			}
		}

	}

	//출력
	cout << ans;
}