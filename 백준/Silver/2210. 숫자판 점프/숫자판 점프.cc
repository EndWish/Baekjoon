#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0 ,-1,1};
array<array<int, 5>, 5> board;
array<bool, 1000000> visit;

void DFS(int r, int c, int cnt, int num);
bool Inside(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	for (int i = 0; i < board.size(); ++i)
		for (int j = 0; j < board.size(); ++j)
			cin >> board[i][j];

	//문제해결
	for (int i = 0; i < board.size(); ++i)
		for (int j = 0; j < board.size(); ++j)
			DFS(i, j, 0, 0);
	
	//출력
	cout << count(visit.begin(), visit.end(), true);

}

void DFS(int r, int c, int cnt, int num) {
	if (cnt == 6) {
		visit[num] = true;
		return;
	}

	for (int i = 0; i < 4; ++i) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (!Inside(nr, nc))
			continue;

		int nextNum = num * 10 + board[r][c];
		DFS(nr, nc, cnt + 1, nextNum);
	}
}

bool Inside(int r, int c) {
	if (r < 0 || 5 <= r || c < 0 || 5 <= c)
		return false;
	return true;
}
