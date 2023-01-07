#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXN 1001

int n, m;
array<vector<int>, MAXN> edges;
array<int, MAXN> matchings;
array<bool, MAXN> finished;

bool Match(int worker);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	
	for (int i = 1; i <= n; ++i) {
		int num;
		cin >> num;
		edges[i].assign(num, {});
		for (int& edge : edges[i])
			cin >> edge;
	}

	//문제해결
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		finished.fill(false);
		if (Match(i))
			++ans;
	}

	//출력
	cout << ans;

}

bool Match(int worker) {
	for (int work : edges[worker]) {
		if (finished[work])
			continue;

		if (matchings[work] == 0) {	// work번 일이 배정되지 않았다면
			matchings[work] = worker;
			return true;
		}
		else {
			finished[work] = true;
			if (Match(matchings[work])) {	// work번 일에 대해 양보가 가능하다면
				matchings[work] = worker;
				return true;
			}
		}
	}
	return false;
}
