#include <iostream>
#include <set>

#define MAXN 1001

using namespace std;

int dr[] = { 0,0,-1,1 };
int dc[] = { -1,1,0,0 };

int n, m;
int board[MAXN][MAXN];

int idCnt = 2;
int groupNum[MAXN * MAXN];

int MoveNum(int r, int c);
void MakeGroupDFS(int r, int c);
bool Inside(int r, int c);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> m;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			char ch;
			cin >> ch;
			board[r][c] = (int)(ch - '0');
		}
	}	

	//문제해결
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			if (board[r][c] == 0) {
				MakeGroupDFS(r, c);
				++idCnt;
			}
		}
	}

	//출력
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			if (board[r][c] == 1) {	// 벽일 경우
				cout << MoveNum(r, c) % 10;
			}
			else {	// 빈 칸인 경우
				cout << 0;
			}
		}
		cout << "\n";
	}

}

int MoveNum(int r, int c) {
	set<int> s;
	for (int i = 0; i < 4; ++i) {
		int nr = r + dr[i];
		int nc = c + dc[i];

		if (Inside(nr, nc) && board[nr][nc] != 1)
			s.insert(board[nr][nc]);
	}

	int res = 1;
	for (int id : s)
		res += groupNum[id];

	return res;
}

void MakeGroupDFS(int r, int c) {
	board[r][c] = idCnt;
	++groupNum[idCnt];

	for (int i = 0; i < 4; ++i) {
		int nr = r + dr[i];
		int nc = c + dc[i];

		if(Inside(nr, nc) && board[nr][nc] == 0)
			MakeGroupDFS(nr, nc);
	}
}

bool Inside(int r, int c) {
	if (r < 0 || n <= r || c < 0 || m <= c)
		return false;
	return true;
}
