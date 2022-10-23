#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

int n;
vector<int> board;
vector<int> visit;
int a, b;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	board.assign(n + 1, {});
	visit.assign(n + 1, -1);

	for (int& val : board | views::drop(1))
		cin >> val;
	cin >> a >> b;

	//문제해결
	queue<int> q;
	q.push(a);
	visit[a] = 0;
	while (!q.empty()) {
		int x = q.front();
		q.pop();

		int nx = x % board[x] == 0 ? board[x] : x % board[x];
		while (true) {
			if (visit[nx] == -1) {
				q.push(nx);
				visit[nx] = visit[x] + 1;
			}

			nx += board[x];
			if (n < nx)
				break;
		}
	}

	//출력
	cout << visit[b];

}