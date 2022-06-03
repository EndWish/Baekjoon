#include <iostream>
#include <algorithm>
#include <array>

#define MAXN 50

using namespace std;

int n, m;
array<array<char, MAXN>, MAXN> board;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> board[i][j];
			board[i][j] -= '0';
		}
	}

	//문제해결
	int lenMin = 1;
	int ans = 1;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {	// 왼쪽위 꼭짓점의 위치

			int lenMax = min(n - 1 - r, m - 1 - c);

			for (int len = lenMin; len <= lenMax; ++len) {	// 정사각형 한 변의 길이 - 1
				if (board[r][c] != board[r][c + len])
					continue;
				if (board[r][c] != board[r + len][c])
					continue;
				if (board[r][c] != board[r + len][c + len])
					continue;
				
				int area = (len + 1) * (len + 1);
				if (area > ans) {
					ans = area;
					lenMin = len + 1;
				}

			}
			
		}
	}
	
	//출력
	cout << ans;

}