#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <cmath>

using namespace std;

#define MAXN 100

int n, m;
array<vector<int>, MAXN + 1> edges;
array<int, MAXN + 1> managers;
array<bool, MAXN + 1> finish;

int MaximumMatching();
bool DFS(int worker);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	// 입력받기
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		edges[a].push_back(b);
	}

	// 문제해결
	cout << MaximumMatching();
}

int MaximumMatching() {
	int result = 0;
	fill_n(&managers[0], MAXN + 1, -1);
	for (int worker = 1; worker <= n; ++worker) {
		fill_n(&finish[0], MAXN + 1, false);
		if (DFS(worker))
			++result;
	}
	return result;
}

bool DFS(int worker) {
	for (int work : edges[worker]) {
		if (finish[work])
			continue;

		if (managers[work] == -1) {
			managers[work] = worker;
			return true;
		}

		finish[work] = true;
		if (DFS(managers[work])) {	// 현재 work의 담당자가 다른일을 맡아서 일을 양보받을 수 있을 경우
			managers[work] = worker;
			return true;
		}
	}

	return false;
}
