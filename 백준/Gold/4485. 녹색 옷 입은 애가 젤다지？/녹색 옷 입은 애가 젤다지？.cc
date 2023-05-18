#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

struct Tuple {
	int a, b, c;
	Tuple(int a, int b, int c) : a{ a }, b{ b }, c{ c }{

	}

	bool operator<(const Tuple& other) const {
		return this->a < other.a;
	}
	bool operator>(const Tuple& other) const {
		return this->a > other.a;
	}
};

#define pii pair<int,int>

int dr[] = { 0,0,-1,1 };
int dc[] = { -1,1,0,0 };

int n;
array<array<int, 125>, 125> board, dp;
priority_queue<Tuple, vector<Tuple>, greater<Tuple>> pq;

void InputBoard();
bool IsInside(int r, int c);
void PrintBoard();

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int testCaseNum = 1;
	while (cin >> n) {
		if (n == 0)
			break;

		InputBoard();
		fill_n(&dp[0][0], 125 * 125, -1);
		pq.emplace(board[0][0], 0, 0);

		while (!pq.empty()) {
			auto [num, r, c] = pq.top();
			pq.pop();

			// 이미 갱신이 된 곳일 경우 스킵한다.
			if (dp[r][c] != -1 && dp[r][c] <= num)
				continue;

			// 최단거리를 갱신해 준다.
			dp[r][c] = num;

			// 최종 목적지에 도달한 경우 루프를 빠져 나온다.
			if (r == n - 1 && c == n - 1) {
				break;
			}

			// 주위에 갱신될 수 있는 곳들을 추가한다.
			for (int i = 0; i < 4; ++i) {
				int nr = r + dr[i];
				int nc = c + dc[i];
				if (IsInside(nr, nc) && (dp[nr][nc] == - 1 || dp[r][c] + board[nr][nc] < dp[nr][nc])) {
					pq.emplace(dp[r][c] + board[nr][nc], nr, nc);
				}
			}
		}

		//PrintBoard();

		while (!pq.empty())
			pq.pop();

		cout << "Problem " << testCaseNum << ": " << dp[n - 1][n - 1] << "\n";
		++testCaseNum;
	}
	
}

void InputBoard() {
	
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			cin >> board[r][c];
		}
	}
}

bool IsInside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < n;
}

void PrintBoard() {
	cout << "dp : \n";
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			cout << dp[r][c] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}