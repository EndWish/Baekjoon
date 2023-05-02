#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n, m, k;
array<array<bool, 50>, 50> initBoard, board;

int LineTurnOn(int row);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			char ch;
			cin >> ch;
			initBoard[r][c] = ch - '0';
		}
	}
	cin >> k;

	int ans = 0;
	for (int r = 0; r < n; ++r) {
		ans = max(ans, LineTurnOn(r));
	}
	cout << ans;

}

int LineTurnOn(int row) {
	board = initBoard;

	int count = k;
	for (int c = 0; c < m; ++c) {
		// 불이 꺼져 있는 경우
		if(!board[row][c]) {
			if (count < 0)
				return 0;
			--count;
			for (int r = 0; r < n; ++r) {
				board[r][c] = !board[r][c];
			}
		}
	}

	if (count & 1)
		return 0;

	int result = 0;
	for (int r = 0; r < n; ++r) {
		bool success = true;
		for (int c = 0; c < m; ++c) {
			if (!board[r][c]) {
				success = false;
				continue;
			}
		}
		if (success)
			++result;
	}
	return result;
}
