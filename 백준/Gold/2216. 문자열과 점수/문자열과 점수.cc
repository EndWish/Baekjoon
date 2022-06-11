#include <iostream>
#include <string>
#include <ranges>
#include <array>
#include <algorithm>
#include <numeric>

#define MAXN 3001

using namespace std;

string x, y;
int a, b, c;

array<array<int, MAXN>, MAXN> board;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> a >> b >> c;
	cin >> x >> y;
	x.insert(x.begin(), ' ');
	y.insert(y.begin(), ' ');
	int xLen = x.size();
	int yLen = y.size();
	for (int i = 0; i < xLen; ++i)
		board[i][0] = i * b;
	for (int i = 0; i < yLen; ++i)
		board[0][i] = i * b;

	//문제해결
	for (int i = 1; i < yLen; ++i) {
		for (int j = 1; j < xLen; ++j) {

			if (x[j] == y[i])	// 두 문자가 같을 경우
				board[j][i] = board[j - 1][i - 1] + a;
			else
				board[j][i] = max(board[j - 1][i - 1] + c, max(board[j - 1][i], board[j][i - 1]) + b);
		}
	}

	//출력
	cout << board[xLen - 1][yLen - 1];

}