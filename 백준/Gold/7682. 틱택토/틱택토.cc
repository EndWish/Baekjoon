#include <iostream>
#include <array>
#include <string>
#include <ranges>

using namespace std;

string input;
array<array<char, 3>, 3> board;

pair<int, int> GetXONum();
pair<int, int> GetX3O3Num();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	while (cin >> input) {
		//최기화,입력값 받기
		if (input == "end"s)
			break;

		for (int i = 0; i < input.size(); ++i)
			board[i % 3][i / 3] = input[i];	// x, y

		//문제해결
		int isVaild = false;

		auto [Xnum, Onum] = GetXONum();
		auto [X3num, O3num] = GetX3O3Num();
		if (Xnum == Onum) {	// O가 마지막으로 뒀을 경우
			// X의 3연속이 없어야한다.
			if (X3num == 0) {
				if (Xnum + Onum == 9)	// 모든곳에 두었을 경우
					isVaild = true;
				else
					if (O3num > 0)
						isVaild = true;
			}
		}
		else if (Xnum == Onum + 1) {	// X가 마지막으로 뒀을 경우
			// O의 3연속이 없어야한다.
			if (O3num == 0) {
				if (Xnum + Onum == 9)	// 모든곳에 두었을 경우
					isVaild = true;
				else
					if (X3num > 0)
						isVaild = true;
			}
		}

		//출력
		if (isVaild)
			cout << "valid\n";
		else
			cout << "invalid\n";
	}

}

pair<int, int> GetXONum() 
{
	int Xnum = 0, Onum = 0;

	for(auto row : board)
		for (char c : row) {
			if (c == 'X')
				++Xnum;
			else if (c == 'O')
				++Onum;
		}

	return { Xnum, Onum };
}

pair<int, int> GetX3O3Num() 
{
	int Xnum = 0, Onum = 0;

	for (int i = 0; i < 3; ++i) {
		if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) {	// 3개의 칸이 같으면
			if (board[i][0] == 'X')
				++Xnum;
			if (board[i][0] == 'O')
				++Onum;
		}
		if (board[0][i] == board[1][i] && board[0][i] == board[2][i]) {	// 3개의 칸이 같으면
			if (board[0][i] == 'X')
				++Xnum;
			if (board[0][i] == 'O')
				++Onum;
		}
	}

	if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {	// 대각선1
		if (board[0][0] == 'X')
			++Xnum;
		if (board[0][0] == 'O')
			++Onum;
	}

	if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {	// 대각선2
		if (board[0][2] == 'X')
			++Xnum;
		if (board[0][2] == 'O')
			++Onum;
	}

	return { Xnum, Onum };
}
