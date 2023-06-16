#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <deque>

using namespace std;

#define MAXN 102
#define pii pair<int,int>

int dr[] = { 0,0,-1,1 };
int dc[] = { -1,1,0,0 };

int h, w;
array<array<char, MAXN>, MAXN> board;
array<array<array<int, MAXN>, MAXN>, 3> dp;
array<pii, 3> start;

int Solve();
void BFS(int starter);
bool IsInside(int r, int c);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	// 초기화
	start[0] = { 0,0 };

	// 입력받기
	int t;
	cin >> t;

	while (t-- > 0) {
		int startCount = 1;

		cin >> h >> w;
		// 내용물을 채운다.
		for (int r = 1; r <= h; ++r) {
			for (int c = 1; c <= w; ++c) {
				cin >> board[r][c];
				if (board[r][c] == '$') {
					start[startCount] = { r, c };
					++startCount;
				}
			}
		}

		// 테두리를 채우기 위해 h와 w를 2칸씩 늘린다.
		h += 2;
		w += 2;

		// 테두리를 공백으로 채운다.
		for (int r = 0; r < h; ++r) {
			board[r][0] = '.';
			board[r][w - 1] = '.';
		}
		for (int c = 0; c < w; ++c) {
			board[0][c] = '.';
			board[h - 1][c] = '.';
		}

		// 문제해결
		cout << Solve() << "\n";

	}
	
	
}

int Solve() {

	for (int i = 0; i < 3; ++i) {
		BFS(i);
	}
	
	int result = numeric_limits<int>::max();
	for (int r = 0; r < h; ++r) {
		for (int c = 0; c < w; ++c) {
			// 벽이거나 방문하지 못하는 곳일 경우 무시한다.(한명이라도 방문 못하면 모두다 방문 불가능)
			if (board[r][c] == '*' || dp[0][r][c] == -1)
				continue;

			int dpSum = 0;
			for (int i = 0; i < 3; ++i)
				dpSum += dp[i][r][c];
			if (board[r][c] == '#')
				dpSum -= 2;

			result = min(result, dpSum);\

		}
	}

	return result;
}

void BFS(int starter) {
	// 초기화
	fill_n(&dp[starter][0][0], MAXN * MAXN, -1);

	deque<pii> deq;
	deq.push_back(start[starter]);
	dp[starter][start[starter].first][start[starter].second] = 0;
	while (!deq.empty()) {
		auto [r, c] = deq.front();
		deq.pop_front();
		int mydp = dp[starter][r][c];

		// 주변에 있는 타일로 이동한다.
		for (int i = 0; i < 4; ++i) {
			int nr = r + dr[i];
			int nc = c + dc[i];

			// 범위 밖이거나 / 벽이거나 / 이미 방문했다면 무시한다.
			if (!IsInside(nr, nc) || board[nr][nc] == '*' || dp[starter][nr][nc] != -1)
				continue;
			
			// 문일경우
			if (board[nr][nc] == '#') {
				deq.emplace_back(nr, nc);
				dp[starter][nr][nc] = mydp + 1;
			}
			// 공백일 경우(죄수 위치 포함)
			else {
				deq.emplace_front(nr, nc);
				dp[starter][nr][nc] = mydp;
			}
		}
	}
}

bool IsInside(int r, int c) {
	return 0 <= r && r < h && 0 <= c && c < w;
}
