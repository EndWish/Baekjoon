#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>

using namespace std;

int n, m;
vector<vector<int>> board;
vector<vector<int>> fenwick;

void Update(int r, int c, int add);
int Sum(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	board.assign(n + 1, vector<int>(n + 1, 0));
	fenwick.assign(n + 1, vector<int>(n + 1, 0));
	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= n; ++c) {
			cin >> board[r][c];
			Update(r, c, board[r][c]);
		}
	}

	//문제해결
	int w, r1, c1, p, r2, c2;
	for (int i = 0; i < m; ++i) {
		cin >> w;
		if (w == 0) {
			cin >> r1 >> c1 >> p;
			Update(r1, c1, p - board[r1][c1]);
			board[r1][c1] = p;
		}
		else if (w == 1) {
			cin >> r1 >> c1 >> r2 >> c2;
			if (r1 > r2) swap(r1, r2);
			if (c1 > c2) swap(c1, c2);
			cout << Sum(r2, c2) - Sum(r2, c1 - 1) - Sum(r1 - 1, c2) + Sum(r1 - 1, c1 - 1) << "\n";
		}
	}

	//출력

}

void Update(int r, int c, int add) {
	for (int row = r; row <= n; row += row & -row) {
		for (int col = c; col <= n; col += col & -col) {
			fenwick[row][col] += add;
		}
	}
}

int Sum(int r, int c) {
	int result = 0;
	for (int row = r; 0 < row; row -= row & -row)
		for (int col = c; 0 < col; col -= col & -col)
			result += fenwick[row][col];
	return result;
}
