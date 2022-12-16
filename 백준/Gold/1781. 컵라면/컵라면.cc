#include <iostream>
#include <queue>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define pii pair<int, int>

int n;
priority_queue<pii, vector<pii>, greater<pii>> pq;
priority_queue<int, vector<int>, greater<int>> anses;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	int deadline, noodle;
	for (int i = 0; i < n; ++i) {
		cin >> deadline >> noodle;
		pq.emplace(deadline, noodle);
	}

	//문제해결
	while (!pq.empty()) {
		tie(deadline, noodle) = pq.top();
		pq.pop();

		if (anses.size() < deadline) {
			anses.push(noodle);
		}
		else if(anses.top() < noodle) {
			anses.pop();
			anses.push(noodle);
		}
	}

	//출력
	int ans = 0;
	while (!anses.empty()) {
		ans += anses.top();
		anses.pop();
	}
	cout << ans;

}

