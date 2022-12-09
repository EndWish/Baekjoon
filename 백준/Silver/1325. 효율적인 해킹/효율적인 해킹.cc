#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define MAXN 10'001

// 효율적인 해킹

int n, m;
vector<int> edge[MAXN];
array<bool, MAXN> visit;
vector<int> ans;
int maxHeck = 0;

int DFS(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		edge[b].push_back(a);
	}

	//문제해결
	for (int i = 1; i <= n; ++i) {
		visit.fill(false);
		int result = DFS(i);
		if (result == maxHeck) {
			ans.push_back(i);
		}
		else if (maxHeck < result) {
			maxHeck = result;
			ans.clear();
			ans.push_back(i);
		}
	}

	//출력
	ranges::sort(ans);
	for (int val : ans)
		cout << val << " ";

}

int DFS(int node) {
	visit[node] = true;
	int result = 1;
	for (int i = 0; i < edge[node].size(); ++i) {
		int nextNode = edge[node][i];
		if (!visit[nextNode]) {
			result += DFS(nextNode);
		}
	}
	return result;
}
