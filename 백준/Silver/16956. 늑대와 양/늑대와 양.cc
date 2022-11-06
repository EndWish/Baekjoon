#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define MAXN 500
int dr[] = { 1,-1,0,0 };
int dc[] = { 0,0,1,-1 };

int n, m;
array<array<char, MAXN>, MAXN> board;

bool Inside(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	//초기화,입력값 받기
	cin >> n >> m;
	for (int r = 0; r < n; ++r)
		for (int c = 0; c < m; ++c)
			cin >> board[r][c];

	//문제해결
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			if (board[r][c] != 'W')
				continue;

			for (int i = 0; i < 4; ++i) {
				int nr = r + dr[i];
				int nc = c + dc[i];

				if (!Inside(nr, nc))
					continue;

				if (board[nr][nc] == '.' || board[nr][nc] == 'D')
					board[nr][nc] = 'D';
				else if (board[nr][nc] == 'S') {
					cout << 0;
					return 0;
				}
			}
		}
	}

	//출력
	cout << 1 << endl;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cout << board[r][c];
		}
		cout << endl;
	}

}

bool Inside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}
