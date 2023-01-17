#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>

using namespace std;

#define MAXM 1001

int n, m;
array<vector<int>, MAXM> edges;
array<array<int, 2>, MAXM> matching;
array<array<int, 2>, MAXM> visit;

bool Match(int work);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	ranges::fill_n(&matching[0][0], MAXM * 2, -1);

	cin >> n >> m;
	for (int worker = 1; worker <= n; ++worker) {
		int num;
		cin >> num;
		int work;
		for (int i = 0; i < num; ++i) {
			cin >> work;
			edges[work].push_back(worker);
		}
	}

	//문제해결
	int ans = 0;
	for (int work = 1; work <= m; ++work) {
		ranges::fill_n(&visit[0][0], MAXM * 2, false);
		if (Match(work))
			++ans;
	}

	cout << ans;

}

bool Match(int work) {

	for (int worker : edges[work]) {
		for (int i = 0; i < 2; ++i) {
			if (visit[worker][i])
				continue;

			if (matching[worker][i] == -1) {
				matching[worker][i] = work;
				return true;
			}
			else {
				visit[worker][i] = true;
				if (Match(matching[worker][i])) {
					matching[worker][i] = work;
					return true;
				}
			}
		}
	}


	return false;
}
