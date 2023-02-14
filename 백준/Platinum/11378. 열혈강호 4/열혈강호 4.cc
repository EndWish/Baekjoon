#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXN 1'001

int n, m, k;
array<vector<int>, MAXN> edges;
array<int, MAXN> visit;
array<bool, MAXN> finished;

bool DFS(int worker);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	fill_n(&visit[0], MAXN, -1);

	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i) {
		int nWork;
		cin >> nWork;
		for (int j = 0; j < nWork; ++j) {
			int work;
			cin >> work;
			edges[i].push_back(work);
		}
	}

	//문제해결
	int ans = 0;
	for (int worker = 1; worker <= n; ++worker) {
		fill_n(&finished[0], MAXN, false);
		if (DFS(worker))
			++ans;
	}
	for (int worker = 1; worker <= n; ++worker) {
		while (0 < k) {
			fill_n(&finished[0], MAXN, false);
			if (DFS(worker)) {
				--k;
				++ans;
			}
			else {
				break;
			}
		}
	}

	cout << ans;
}

bool DFS(int worker) {
	for (int work : edges[worker]) {


		if (visit[work] == -1) {
			visit[work] = worker;
			return true;
		}
		else if(!finished[work]) {
			finished[work] = true;
			if (DFS(visit[work])) {
				visit[work] = worker;
				return true;
			}
		}
	}
	return false;
}
