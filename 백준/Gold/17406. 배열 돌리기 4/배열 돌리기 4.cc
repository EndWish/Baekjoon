#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXN 51
#define pii pair<int,int>
#define piii pair<pii,int>

int dr[4] = { 0, 1, 0, -1 };
int dc[4] = { 1, 0, -1, 0 };

int n, m, k;
array<array<int, MAXN>, MAXN> InitBoard;
array<array<int, MAXN>, MAXN> board;
vector<piii> cmds;

void Rotate(int cr, int cc, int s);
void RotateOutLine(int cr, int cc, int r);
void Print();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m >> k;

	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= m; ++c) {
			cin >> InitBoard[r][c];
		}
	}

	for (int i = 0; i < k; ++i) {
		piii cmd;
		cin >> cmd.first.first >> cmd.first.second >> cmd.second;
		cmds.push_back(cmd);
	}

	int ans = numeric_limits<int>::max();
	ranges::sort(cmds);
	do {
		// 명령을 수행한다.
		board = InitBoard;
		for (piii& cmd : cmds)
			Rotate(cmd.first.first, cmd.first.second, cmd.second);

		// 배열의 값을 얻는다.
		int arrayValue = numeric_limits<int>::max();
		for (int r = 1; r <= n; ++r) {
			int sum = 0;
			for (int c = 1; c <= m; ++c) {
				sum += board[r][c];
			}
			arrayValue = min(arrayValue, sum);
		}
		ans = min(ans, arrayValue);

	} while (ranges::next_permutation(cmds).found);

	cout << ans;
}

void Rotate(int cr, int cc, int s) {
	for (int i = 1; i <= s; ++i) {
		RotateOutLine(cr, cc, i);
	}
}
void RotateOutLine(int cr, int cc, int r) {
	pii path[5] = { {cr - r, cc - r},{cr - r, cc + r},{cr + r, cc + r},{cr + r, cc - r},{cr - r, cc - r} };
	
	vector<int> rotateNum;
	for (int i = 0; i < 4; ++i) {
		pii s = path[i];
		while (s != path[i + 1]) {
			rotateNum.push_back(board[s.first][s.second]);
			s.first += dr[i];
			s.second += dc[i];
		}
	}

	ranges::rotate(rotateNum, rotateNum.end() - 1);
	int index = 0;
	for (int i = 0; i < 4; ++i) {
		pii s = path[i];
		while (s != path[i + 1]) {
			board[s.first][s.second] = rotateNum[index++];
			s.first += dr[i];
			s.second += dc[i];
		}
	}
}

void Print() {
	cout << "\n";
	for (int r = 1; r <= n; ++r) {
		for (int c = 1; c <= m; ++c) {
			cout << board[r][c] << " ";
		}
		cout << "\n";
	}
}
