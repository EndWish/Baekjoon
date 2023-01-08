#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXN 501

int t, n, m;

vector<int> ranking;
array<array<bool, MAXN>, MAXN> edges;	// edges[i][j]가 true면 i -> j
array<int, MAXN> priority;	// edges[i][j]가 true면 i -> j


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> t;
	while (t-- > 0) {
		//초기화,입력값 받기
		priority.fill(0);

		cin >> n;
		ranking.assign(n, {});
		for (int i = 0; i < n; ++i) {
			cin >> ranking[i];
			for (int j = 0; j < i; ++j) {
				edges[ranking[i]][ranking[j]] = true;
				edges[ranking[j]][ranking[i]] = false;
			}
			priority[ranking[i]] = n - 1 - i;
		}

		cin >> m;
		for (int i = 0; i < m; ++i) {
			int a, b;
			cin >> a >> b;
			edges[a][b] = !edges[a][b];
			edges[b][a] = !edges[b][a];
			if (edges[a][b]) {
				++priority[b];
				--priority[a];
			}
			else {
				--priority[b];
				++priority[a];
			}
		}

		//문제해결
		queue<int> q;
		for (int i = 1; i <= n; ++i) {
			if (priority[i] == 0)
				q.push(i);
		}

		int result = -1;
		vector<int> ans;
		ans.reserve(n);
		while (!q.empty()) {
			if (q.size() > 1) {
				result = 0;
				break;
			}
			int x = q.front();
			q.pop();
			ans.push_back(x);
			
			for (int next = 1; next <= n; ++next) {
				if (edges[x][next]) {
					--priority[next];
					if (priority[next] == 0)
						q.push(next);
					else if (priority[next] < 0) {	// 사이클이 존재
						result = 1;
						break;
					}
				}
			}

			if (result == 1)
				break;
		}

		if (ans.size() != n)
			result = 1;

		//출력
		if (result == 0)
			cout << "?\n";
		else if (result == 1)
			cout << "IMPOSSIBLE\n";
		else {
			for (int num : ans | views::reverse)
				cout << num << " ";
			cout << "\n";
		}
	}

}
