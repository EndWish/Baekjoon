#include <iostream>
#include <queue>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define pii pair<int, int>

int m;


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int t;
	cin >> t;
	while (t-- > 0) {
		//초기화,입력값 받기
		priority_queue<int> first;
		priority_queue<int, vector<int>, greater<int>> second;
		cin >> m;

		cout << m / 2 + 1 << "\n";

		//문제해결
		for (int i = 1; i <= m; ++i) {
			int input;
			cin >> input;

			if (!first.empty() && input < first.top()) {
				first.push(input);
				while (first.size() > second.size() + 1) {
					int x = first.top();
					first.pop();
					second.push(x);
				}
			}
			else {
				second.push(input);
				while (first.size() < second.size()) {
					int x = second.top();
					second.pop();
					first.push(x);
				}
			}

			//출력
			if (i & 1)
				cout << first.top() << " ";
		}

		cout << "\n";
	}


}

