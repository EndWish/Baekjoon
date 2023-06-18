#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <queue>

using namespace std;

#define pii pair<int,int>

int n, m, k;
int d;
array<vector<int>, 1001> edges;	// edges[worker] = {works}
array<int, 1001> match;	// match[work] = work를 담당하는 사람
array<int, 1001> visit;

bool DFS(int worker);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	// 초기화
	ranges::fill_n(&match[0], 1001, -1);

	// 입력받기
	cin >> n >> m >> k;
	for (int worker = 1; worker <= n; ++worker) {
		int nWork, work;
		cin >> nWork;
		for (int j = 0; j < nWork; ++j) {
			cin >> work;
			edges[worker].push_back(work);
		}
	}
	
	// 문제해결
	int ans = 0;
	for (int work = 1; work <= m; ++work) {
		ranges::fill_n(&visit[0], 1001, false);
		if (DFS(work))
			++ans;
	}
	int nDouble = 0;
	for (int work = 1; work <= m; ++work) {
		ranges::fill_n(&visit[0], 1001, false);
		if (DFS(work)) {
			++ans;
			if (++nDouble >= k)
				break;
		}
	}
	cout << ans;

}

bool DFS(int worker) {
	for (int work : edges[worker]) {
		if (visit[work])
			continue;

		if (match[work] == -1) {
			match[work] = worker;
			return true;
		}
		visit[work] = true;
		if (DFS(match[work])) {
			match[work] = worker;
			return true;
		}
	}

	return false;
}
