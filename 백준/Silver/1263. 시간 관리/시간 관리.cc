#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define pii pair<int,int>

int n;
vector<pii> work;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	work.assign(n, {});
	for (auto& [t, s] : work)
		cin >> t >> s;

	//문제해결
	ranges::sort(work, greater<int>{}, & pii::second);
	int start = numeric_limits<int>::max();
	for (auto [t, s] : work) {
		if (s < start) {
			start = s;
		}
		start -= t;
	}

	//출력
	if (0 < start)
		cout << start;
	else
		cout << -1;
}
