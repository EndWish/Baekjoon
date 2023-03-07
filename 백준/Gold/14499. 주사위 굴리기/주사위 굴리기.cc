#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int dr[5] = { 0, 0,0,-1,1 };
int dc[5] = { 0, 1,-1,0,0 };

int n, m, diceR, diceC, k;
array<int, 6> nums;	// 위0, 아래1, 동2, 서3, 북4, 남5
array<array<int, 20>, 20> board;

void RotateDice(int cmd);
bool Inside(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m >> diceR >> diceC >> k;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> board[r][c];
		}
	}

	//문제해결
	for (int i = 0; i < k; ++i) {
		int cmd;
		cin >> cmd;
		int nr = diceR + dr[cmd];
		int nc = diceC + dc[cmd];
		if (Inside(nr, nc)) {
			RotateDice(cmd);
			diceR = nr;
			diceC = nc;
			// 칸에 쓰여있는 수가 0이면
			if (board[diceR][diceC] == 0) {
				board[diceR][diceC] = nums[1];
			}
			// 칸에 쓰여있는 수가 0이 아니면
			else {
				nums[1] = board[diceR][diceC];
				board[diceR][diceC] = 0;
			}
			cout << nums[0] << "\n";
		}
	}

}

void RotateDice(int cmd) {
	vector<int> indices;
	switch (cmd) {
	case 1:	// 동쪽
		indices = { 0, 2, 1, 3 }; break;
	case 2:	// 서쪽
		indices = { 0, 3, 1, 2 }; break;
	case 3:	// 북쪽
		indices = { 0, 4, 1, 5 }; break;
	case 4:	// 남쪽
		indices = { 0, 5, 1, 4 }; break;
	default:
		break;
	}

	int temp = nums[indices[3]];
	for (int i = indices.size() - 1; 1 <= i; --i) {
		int index = indices[i];
		int prevIndex = indices[i - 1];
		nums[index] = nums[prevIndex];
	}
	nums[indices[0]] = temp;
}
bool Inside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}