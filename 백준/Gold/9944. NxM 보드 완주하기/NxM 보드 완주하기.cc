#include <iostream>
#include <array>
#include <algorithm>
#include <memory.h>
#include <numeric>
#include <vector>

using namespace std;

int t;
int dr[] = {1,-1,0,0};
int dc[] = { 0,0,1,-1};

array<array<char, 30>, 30> board;
array<array<bool, 30>, 30> visit;
int n, m;
int nBlank;
int nVisit;
int ans;

bool Inside(int r, int c);
bool IsEmpty(int r, int c);
void DFS(int r, int c, int rotation);
void Print();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	while (cin >> n >> m) {
		++t;
		//최기화,입력값 받기
		nBlank = n * m;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				cin >> board[i][j];
				if (board[i][j] == '*')
					--nBlank;
			}
		}

		memset(&visit[0][0], false, sizeof(visit));
		ans = numeric_limits<int>::max();
		nVisit = 0;

		//문제해결
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (board[i][j] == '.') {
					visit[i][j] = true;
					++nVisit;
					DFS(i, j, 0);
					visit[i][j] = false;
					--nVisit;
				}
			}
		}

		//출력
		if (ans == numeric_limits<int>::max())
			cout << "Case " << t << ": " << - 1 << "\n";
		else
			cout << "Case " << t << ": " << ans << "\n";

	}
}

bool Inside(int r, int c) {
	if (r < 0 || n <= r || c < 0 || m <= c)
		return false;
	return true;
}

bool IsEmpty(int r, int c) {
	if (Inside(r, c) && !visit[r][c] && board[r][c] == '.')
		return true;
	return false;
}

void DFS(int r, int c, int rotation) {
	//Print();

	vector<pair<int, int>> restore;
	restore.reserve(n + m);

	for (int i = 0; i < 4; ++i) {
		int nr = r + dr[i];
		int nc = c + dc[i];

		if (IsEmpty(nr, nc)) {	// 막혀있지 않을 경우

			// 이동하는 경로 방문처리
			restore.clear();

			int vr = nr;
			int vc = nc;
			while (IsEmpty(vr, vc)) {
				restore.push_back({ vr, vc });
				visit[vr][vc] = true;
				++nVisit;
				vr += dr[i];
				vc += dc[i];
			}

			// DFS 재귀
			DFS(vr - dr[i], vc - dc[i], rotation + 1);

			// 방문처리 원상복구
			for (const auto& [r, c] : restore) {
				visit[r][c] = false;
				--nVisit;
			}

		}
		else {	//막혀있을 경우
			if (nVisit == nBlank)	// 모든 빈칸을 방문 했을 경우
				ans = min(ans, rotation);
		}
	}
}

void Print() {
	cout << "--------------------------------\n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (board[i][j] == '*')
				cout << '*';
			else if (visit[i][j])
				cout << '~';
			else
				cout << '.';
		}
		cout << "\n";
	}
	cout << "--------------------------------\n";
}

