#include <iostream>
#include <array>
#include <queue>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

// 빙산

#define MAXN 300

int dr[] = { 1,-1,0,0 };
int dc[] = { 0,0,1,-1 };

int n, m;
array<array<int, MAXN>, MAXN> board;
array<array<int, MAXN>, MAXN> nextBoard;

array<array<bool, MAXN>, MAXN> visit;

bool Inside(int r, int c);
int IslandNum();
void DFS(int r, int c);
void Advance();
void Print();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	for (int r = 0; r < n; ++r)
		for (int c = 0; c < m; ++c)
			cin >> board[r][c];

	//문제해결
	int year = 0;
	while (true) {
		// 임시 출력
		//cout << "year : " << year << "\n";
		//Print();

		// 두 덩어리인지 판단.
		int islandNum = IslandNum();
		//cout << "덩어리 개수 : " << islandNum << "\n";
		if (islandNum == 0) {
			cout << 0;
			return 0;
		}
		else if (islandNum >= 2) {
			cout << year;
			return 0;
		}

		// 1년 진행
		Advance();
		++year;
	}

	//출력

}

bool Inside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}

int IslandNum() {
	fill_n(&visit[0][0], MAXN * MAXN, false);
	int count = 0;
	for (int r = 1; r < n-1; ++r) {
		for (int c = 1; c < m-1; ++c) {
			if (0 < board[r][c]&& !visit[r][c]) {	// 땅일 경우
				++count;
				DFS(r, c);
			}
		}
	}
	return count;
}
void DFS(int r, int c) {
	visit[r][c] = true;
	for (int i = 0; i < 4; ++i) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (Inside(nr, nc) && !visit[nr][nc] && 0 < board[nr][nc]) {
			DFS(nr, nc);
		}
	}
}

void Advance() {

	for (int r = 1; r < n - 1; ++r) {
		for (int c = 1; c < m - 1; ++c) {
			if (0 < board[r][c]) {
				nextBoard[r][c] = board[r][c];
				for (int i = 0; i < 4; ++i) {
					int nr = r + dr[i];
					int nc = c + dc[i];
					if (Inside(nr, nc) && board[nr][nc] == 0) {
						--nextBoard[r][c];
					}
				}
				if (nextBoard[r][c] < 0)
					nextBoard[r][c] = 0;
			}
		}
	}

	copy_n(&nextBoard[0][0], MAXN * MAXN, &board[0][0]);
}

void Print() {
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cout << board[r][c] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}