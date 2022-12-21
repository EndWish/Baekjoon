#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

#define pii pair<int,int>

int n;
vector<pii> skylines;
stack<int> heights;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	skylines.assign(n, {});
	for (auto& [x, y] : skylines) {
		cin >> x >> y;
	}

	//문제해결
	ranges::sort(skylines);
	int ans = 0;
	for (auto [x, y] : skylines) {
		if (heights.empty() || heights.top() < y) {
			if (0 < y)
				heights.push(y);
		}
		else {
			while (!heights.empty() && heights.top() > y) {
				heights.pop();
				++ans;
			}
			if (heights.empty() || heights.top() != y) {
				if (0 < y)
					heights.push(y);
			}
		}
	}

	ans += heights.size();

	//출력
	cout << ans;
}

