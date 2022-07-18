#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <ranges>

#define pii pair<int,int>

using namespace std;

int n;
vector<pii> lines;
vector<pii> dp;

int preLine[500'001];

set<int> ans;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);	

	//최기화,입력값 받기
	cin >> n;
	lines.assign(n, make_pair(0, 0));
	dp.reserve(n);

	for (int i = 0; i < n; ++i) {
		cin >> lines[i].first >> lines[i].second;
		ans.insert(lines[i].first);
	}

	//문제해결
	
	ranges::sort(lines, {}, &pii::first);
	dp.push_back(lines[0]);
	for (auto [a, b] : lines | views::drop(1)) {
		auto p = ranges::lower_bound(dp, b, {}, &pii::second);
		if (p == dp.end()) {	// 정답 갱신
			preLine[a] = dp.rbegin()->first;
			dp.push_back({ a,b });
		}
		else {
			int indexP = distance(dp.begin(), p);
			dp[indexP] = { a,b };
			if (indexP > 0)
				preLine[a] = dp[indexP - 1].first;
		}
	}

	int exceptLine = dp.rbegin()->first;
	while (exceptLine != 0) {
		ans.erase(exceptLine);
		exceptLine = preLine[exceptLine];
	}

	//출력
	cout << ans.size() << "\n";
	for (int a : ans)
		cout << a << "\n";

}
