#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

int t;
int r, c;
array<array<char, 400>, 400> board;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> t;
	while (t-- > 0) {
		//초기화,입력값 받기
		cin >> r >> c;
		for (int y = 0; y < r; ++y) {
			for (int x = 0; x < c; ++x) {
				cin >> board[y][x];
			}
		}

		//문제해결
		int ans = 0;
		for (int y = 0; y < r; ++y)
			for (int x = 0; x < c - 2; ++x)
				if (board[y][x] == '>' && board[y][x + 1] == 'o' && board[y][x + 2] == '<')
					++ans;
		for (int x = 0; x < c; ++x)
			for (int y = 0; y < r - 2; ++y)
				if (board[y][x] == 'v' && board[y + 1][x] == 'o' && board[y + 2][x] == '^')
					++ans;

		//출력
		cout << ans << "\n";

	}



}