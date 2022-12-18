#include <iostream>
#include <queue>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define pii pair<int,int>

int n;
vector<pii> lectures;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	lectures.assign(n, {});
	for (int i = 0; i < n; ++i) {
		int buffer;
		cin >> buffer >> lectures[i].first >> lectures[i].second;
	}
	ranges::sort(lectures);

	//문제해결
	int ans = 0;
	priority_queue<int, vector<int>, greater<int>> pq;
	for (auto[s, e] : lectures) {
		while (!pq.empty()) {
			if (pq.top() <= s) {
				pq.pop();
			}
			else {
				break;
			}
		}
		pq.push(e);
		ans = max(ans, (int)pq.size());
	}

	//출력
	cout << ans;

}

