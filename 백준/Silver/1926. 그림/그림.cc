#include <iostream>
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

int dr[] = { 1,-1,0,0 };
int dc[] = { 0,0,1,-1 };

int n, m;
array<array<int, 500>, 500> board;
array<array<bool, 500>, 500> visit;
int num;
int maxSize;

bool Inside(int r, int c);
int DFS(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	for (int r = 0; r < n; ++r)
		for (int c = 0; c < m; ++c)
			cin >> board[r][c];
	
	//문제해결
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			if (!visit[r][c] && board[r][c] == 1) {
				++num;
				maxSize = max(maxSize, DFS(r, c));
			}
		}
	}


	//출력
	cout << num << " " << maxSize;

}

bool Inside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}

int DFS(int r, int c) {
	int result = 1;
	visit[r][c] = true;

	for (int i = 0; i < 4; ++i) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (Inside(nr, nc) && board[nr][nc] == 1 && !visit[nr][nc]) {
			result += DFS(nr, nc);
		}
	}
	return result;
}