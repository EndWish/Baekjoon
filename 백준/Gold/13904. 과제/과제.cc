#include <iostream>
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>
//#include <numeric>
//#include <format>

using namespace std;

#define pii pair<int,int> 

int n;
vector<pii> problem;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	problem.assign(n, {});
	for (auto& [d, w] : problem)
		cin >> d >> w;

	//문제해결
	ranges::sort(problem);
	priority_queue<int> pq;
	for (auto[d, w] : problem) {
		if (pq.size() < d)
			pq.push(-w);
		else {
			if (-pq.top() < w) {
				pq.pop();
				pq.push(-w);
			}
		}
	}

	//출력
	int ans = 0;
	while (!pq.empty()) {
		ans += -pq.top();
		pq.pop();
	}

	cout << ans;

}