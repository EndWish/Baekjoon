#include <iostream>
#include <array>
#include <vector>

using namespace std;
array<array<char, 9>, 9> board;
array<array<bool, 10>, 9> rowVisit;	// 열, 숫자
array<array<bool, 10>, 9> colVisit;	// 행, 숫자
array<array<array<bool, 10>, 3>, 3> gridVisit;	// 행칸, 열칸, 숫자

vector<pair<int, int>> blank;

bool DFS(int blankIndex);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	for (int r = 0; r < 9; ++r) {
		for (int c = 0; c < 9; ++c) {
			cin >> board[r][c];
			board[r][c] -= '0';

			if (board[r][c] == 0) {
				blank.emplace_back(r, c);
			}
			else {
				rowVisit[r][board[r][c]] = true;
				colVisit[c][board[r][c]] = true;
				gridVisit[r/3][c/3][board[r][c]] = true;
			}
		}
	}

	//문제해결
	DFS(0);
	
	//출력
	for (int r = 0; r < 9; ++r) {
		for (int c = 0; c < 9; ++c) {
			cout << (char)(board[r][c] + '0');
		}
		cout << "\n";
	}

}

bool DFS(int blankIndex) 
{
	if (blankIndex == blank.size())
		return true;

	auto [r, c] = blank[blankIndex];
	for (int i = 1; i <= 9; ++i) {
		if (rowVisit[r][i] || colVisit[c][i] || gridVisit[r / 3][c / 3][i])
			continue;

		board[r][c] = i;
		rowVisit[r][i] = true;
		colVisit[c][i] = true;
		gridVisit[r / 3][c / 3][i] = true;

		if (DFS(blankIndex + 1))
			return true;

		rowVisit[r][i] = false;
		colVisit[c][i] = false;
		gridVisit[r / 3][c / 3][i] = false;

	}

	board[r][c] = 0;
	return false;
}
