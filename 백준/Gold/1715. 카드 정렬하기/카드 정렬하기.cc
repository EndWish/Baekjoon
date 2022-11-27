#include <iostream>
#include <array>
#include <queue>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

int n;
priority_queue<int, vector<int>, greater<int>> pq;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int input;
		cin >> input;
		pq.push(input);
	}

	//문제해결
	int ans = 0;
	while (1 < pq.size()) {
		int a = pq.top();
		pq.pop();
		int b = pq.top();
		pq.pop();
		ans += a + b;
		pq.push(a + b);
	}

	//출력
	cout << ans;

}
