#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define MAXN 500
#define pii pair<int,int>

int dr[] = { 1,-1,0,0 };
int dc[] = { 0,0, 1,-1 };

int n;
array<array<int, MAXN>, MAXN> board;
array<array<int, MAXN>, MAXN> visit;
queue<pii> q;

bool Inside(int r, int c);
int DFS(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	for (int r = 0; r < n; ++r)
		for (int c = 0; c < n; ++c)
			cin >> board[r][c];

	//문제해결
	int ans = 0;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			if (visit[r][c] == 0) {
				ans = max(ans,DFS(r, c));
			}
		}
	}

	//출력
	cout << ans;
}

bool Inside(int r, int c) {
	if (r < 0 || n <= r || c < 0 || n <= c)
		return false;
	return true;
}

int DFS(int r, int c) {
	if (visit[r][c] != 0)
		return visit[r][c];

	int maxDepth = 1;
	for (int i = 0; i < 4; ++i) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (Inside(nr, nc) && board[nr][nc] > board[r][c]) {
			maxDepth = max(maxDepth, DFS(nr, nc) + 1);
		}
	}

	visit[r][c] = maxDepth;
	return visit[r][c];
}
