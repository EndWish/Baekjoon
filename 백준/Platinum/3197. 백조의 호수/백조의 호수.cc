#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define pii pair<int,int>

int dr[4] = { 1,-1,0,0 };
int dc[4] = { 0,0 ,1,-1};

int n, m;
array<array<char, 1500>, 1500> board;
array<array<char, 1500>, 1500> visitWater;

int area;
int day;
queue<pii> q, waterQ;

bool IsInside(int r, int c);
void AdvanceWater();
bool AdvanceBird();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> board[r][c];
			if (board[r][c] != 'X') {
				waterQ.emplace(r, c);
				visitWater[r][c] = true;
			}
			if (board[r][c] == 'L') {
				q.emplace(r, c);
				board[r][c] = ++area;
			}
		}
	}

	//문제해결
	while (true) {
		bool finish = false;
		// 백조가 이동할 수 있는 경로를 BFS로 탐색
		if (AdvanceBird())
			break;

		// 얼음을 녹여준다.
		AdvanceWater();

		++day;
	}

	cout << day;

}

bool IsInside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}

void AdvanceWater() {
	queue<pii> tempQ;

	// 물을 흘려준다.
	while (!waterQ.empty()) {
		auto [r, c] = waterQ.front();
		waterQ.pop();

		bool inQ = false;
		for (int i = 0; i < 4; ++i) {
			int nr = r + dr[i];
			int nc = c + dc[i];
			if (IsInside(nr, nc)) {
				if (!visitWater[nr][nc] && board[nr][nc] != 'X') {
					waterQ.emplace(nr, nc);
					visitWater[nr][nc] = true;
				}
				else if (board[nr][nc] == 'X' && !inQ) {
					tempQ.emplace(r, c);
					inQ = true;
				}
			}
		}
	}

	// 얼음을 녹여준다.
	while (!tempQ.empty()) {
		auto [r, c] = tempQ.front();
		tempQ.pop();

		for (int i = 0; i < 4; ++i) {
			int nr = r + dr[i];
			int nc = c + dc[i];
			if (IsInside(nr, nc)) {
				if (board[nr][nc] == 'X') {
					board[nr][nc] = '.';
				}
			}
		}
		waterQ.emplace(r, c);
	}
}
bool AdvanceBird() {
	queue<pii> tempQ;

	while (!q.empty()) {
		auto [r, c] = q.front();
		q.pop();

		bool inQ = false;
		for (int i = 0; i < 4; ++i) {
			int nr = r + dr[i];
			int nc = c + dc[i];
			if (IsInside(nr, nc)) {
				// 아직 가보지 않은 물일경우
				if (board[nr][nc] == '.') {
					q.emplace(nr, nc);
					board[nr][nc] = board[r][c];
				}
				// 두 백조가 만날 수 있는 경우
				else if (board[r][c] + board[nr][nc] == 3) {
					return true;
				}
				else if (board[nr][nc] == 'X' && !inQ) {
					tempQ.emplace(r, c);
					inQ = true;
				}
			}
		}
	}

	q = move(tempQ);

	return false;
}
