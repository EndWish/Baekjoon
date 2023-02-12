#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n, m;
array<array<int, 5>, 5> scores = { 
	array<int,5>{10,8,7,5,1},
	array<int,5>{8,6,4,3,1},
	array<int,5>{7,4,3,2,1},
	array<int,5>{5,3,2,2,1},
	array<int,5>{1,1,1,1,0},
};
array<array<char, 14>, 14> board;
vector<vector<int>> dp;	// dp[a][bit] = a번째 칸부터 bit처럼 재워져 있을때 

int DP(int slot, int bit);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	dp.assign(n * m + 1, vector<int>((1 << m), -1));

	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> board[r][c];
			if (board[r][c] == 'F')
				board[r][c] -= 1;
			board[r][c] -= 'A';
		}
	}

	//문제해결
	cout << DP(0, 0);

}

int DP(int slot, int bit) {
	if (n * m <= slot)
		return 0;

	int& val = dp[slot][bit];
	if (val != -1)
		return val;

	int c = slot % m;
	int r = slot / m;

	// 1x1로 자르는 경우
	val = DP(slot + 1, bit >> 1);

	// 세로로 자르는 경우
	if (!(bit & 1) && r < n - 1) {
		char ch[2] = { board[r][c], board[r + 1][c] };
		val = max(val, DP(slot + 1, (bit >> 1) | (1 << (m - 1))) + scores[ch[0]][ch[1]] );
	}

	// 가로로 자르는 경우
	if (!(bit & 0b11) && c < m - 1) {
		char ch[2] = { board[r][c], board[r][c + 1] };
		val = max(val, DP(slot + 2, bit >> 2) + scores[ch[0]][ch[1]]);
	}
	return val;
}
