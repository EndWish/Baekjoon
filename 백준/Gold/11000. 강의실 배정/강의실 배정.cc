#include <iostream>
#include <queue>
#include <vector>
#include <ranges>
#include <algorithm>

using namespace std;

int n;
vector<pair<int, int>> v;
priority_queue<int> pq;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;
	v.assign(n, { 0,0 });
	for (auto& [s, t] : v)
		cin >> s >> t;

	//문제해결
	ranges::sort(v);
	for (const auto& [s, t] : v) {
		if (!pq.empty() && -pq.top() <= s)	// 가능한 강의실이 존재함
			pq.pop();
		pq.push(-t);
	}

	//출력
	cout << pq.size();

}
