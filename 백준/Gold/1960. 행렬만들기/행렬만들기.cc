#include <iostream>
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>

#define MAXN 501

using namespace std;

int n;
int board[MAXN][MAXN];
int row[MAXN];
priority_queue<pair<int, int>> pq;	// 남은 수, 위치

int main() 
{

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> row[i];
	}
	for (int i = 1; i <= n; ++i) {
		int input;
		cin >> input;
		if (input > 0) {
			pq.push({ input, i });
		}
	}

	//문제해결
	for (int i = 1; i <= n; ++i) {
		vector<pair<int, int>> temp;
		while (row[i] > 0) {
			if (pq.empty()) {
				cout << -1;
				return 0;
			}

			auto [num, pos] = pq.top();
			pq.pop();

			board[i][pos] = 1;
			if (num - 1 > 0) {
				temp.emplace_back(num - 1, pos);
			}

			--row[i];
		}

		for (auto t : temp)
			pq.push(t);
	}

	if (!pq.empty()) {
		cout << -1;
		return 0;
	}

	//출력
	cout << 1 << "\n";
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << board[i][j];
		}
		cout << "\n";
	}

}