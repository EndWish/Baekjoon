#include <iostream>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

#define Board array<array<char, 10>, 10>

using namespace std;

int dr[] = { 0, 0, 0, 1, -1 };
int dc[] = { 0, 1, -1, 0, 0 };
Board board;
int ans = 0;

bool Inside(int r, int c);
void PushSwitch(int r, int c, Board& b);
void DFS(int index, int bitmask);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);	

	//최기화,입력값 받기
	ans = numeric_limits<int>::max();
	for (int r = 0; r < 10; ++r)
		for (int c = 0; c < 10; ++c)
			cin >> board[r][c];

	//문제해결
	DFS(0, 0);

	//출력
	if (ans == numeric_limits<int>::max())
		cout << "-1";
	else
		cout << ans;
	
}

bool Inside(int r, int c) {
	if (r < 0 || 10 <= r || c < 0 || 10 <= c)
		return false;
	return true;
}

void PushSwitch(int r, int c, Board& b) {
	for (int i = 0; i < 5; ++i) {
		int nr = r + dr[i];
		int nc = c + dc[i];

		if (Inside(nr, nc)) {
			if (b[nr][nc] == 'O')
				b[nr][nc] = '#';
			else
				b[nr][nc] = 'O';
		}
	}

}

void DFS(int index, int bitmask) {
	if (index == 10) {
		Board tempBoard;
		ranges::copy(board, tempBoard.begin());

		int count = 0;

		for (int c = 0; c < 10; ++c) {
			if ((1 << c) & bitmask) {
				PushSwitch(0, c, tempBoard);
				++count;
			}
		}

		for (int r = 1; r < 10; ++r) {
			for (int c = 0; c < 10; ++c) {
				if (tempBoard[r - 1][c] == 'O') {	// 위에 칸이 전구가 켜져있을 경우
					PushSwitch(r, c, tempBoard);	// 스위치를 눌러 위의 전구를 꺼준다.
					++count;
				}
			}
		}

		if (ranges::all_of(*tempBoard.rbegin(), [](char c) {return c == '#'; })) {
			ans = min(ans, count);
		}
		return;
	}

	DFS(index + 1, bitmask);
	DFS(index + 1, bitmask | (1<<index) );

}
