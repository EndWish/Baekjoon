#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n, m;
array<vector<bool>, 2> guards;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	//초기화,입력값 받기
	cin >> n >> m;
	guards[0].assign(n, false);
	guards[1].assign(m, false);

	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			char ch;
			cin >> ch;
			if (ch == 'X') {
				guards[0][r] = true;
				guards[1][c] = true;
			}
		}
	}

	//문제해결
	cout << max(ranges::count(guards[0], false), ranges::count(guards[1], false));

}
