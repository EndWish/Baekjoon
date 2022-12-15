#include <iostream>
#include <array>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define MAXN 50
#define pii pair<int, int>

int dr[] = { 0,0,1,-1 };
int dc[] = { 1,-1,0,0 };

int n, m;
array<array<char, MAXN>, MAXN> board;
array<array<bool, MAXN>, MAXN> visit;
array<array<int, MAXN>, MAXN> finished;

int DFS(int r, int c);
bool Inside(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> board[r][c];
			if(board[r][c] != 'H')
				board[r][c] -= '0';
		}
	}

	//문제해결
	cout << DFS(0, 0);

	//출력

}

int DFS(int r, int c) {
	visit[r][c] = true;

	int result = 0;
	int x = board[r][c];
	for (int i = 0; i < 4; ++i) {
		int nr = r + dr[i] * x;
		int nc = c + dc[i] * x;
		if (Inside(nr, nc) && board[nr][nc] != 'H') {

			if (finished[nr][nc] != 0) {	// 다음 위치에서 몇번만에 끝이 나는지 확정이 되었다면
				if (finished[nr][nc] == -1) {	// 사이클이 발생하는 노드일 경우
					finished[r][c] = -1;
					return -1;
				}
				else {	// 정상적인 횟수로 끝나는 경우
					result = max(result, finished[nr][nc] + 1);
				}
			}
			else {
				if (visit[nr][nc]) {	// 사이클이 발생한 경우
					finished[r][c] = -1;
					return -1;
				}
				else {
					int dfs = DFS(nr, nc);
					if (dfs == -1) {
						finished[r][c] = -1;
						return -1;
					}
					else {
						result = max(result, dfs + 1);
					}
				}
			}

		}
		else {	// 맵밖으로 나가거나 구멍에 빠지는 경우
			result = max(result, 1);
		}
	}

	finished[r][c] = result;
	return result;
}

bool Inside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}
