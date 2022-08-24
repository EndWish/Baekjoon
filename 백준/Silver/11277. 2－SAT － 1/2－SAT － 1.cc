#include <iostream>
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

int n, m;
vector<bool> var;
vector<pair<int, int>> clause;

bool Solve(int index);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	var.assign(n + 1, false);

	int a, b;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b;
		clause.emplace_back(a, b);
	}

	//문제해결
	if (Solve(1)) {
		cout << 1;
	}
	else {
		cout << 0;
	}

	//출력

}

bool Solve(int index) {
	if (n < index) {
		for (auto [index1, index2] : clause) {
			bool a = index1 > 0 ? var[index1] : !var[-index1];
			bool b = index2 > 0 ? var[index2] : !var[-index2];
			if (!(a || b)) {
				return false;
			}
		}
		return true;
	}

	var[index] = false;
	if (Solve(index + 1)) {
		return true;
	}
	var[index] = true;
	if (Solve(index + 1)) {
		return true;
	}
	return false;
}
