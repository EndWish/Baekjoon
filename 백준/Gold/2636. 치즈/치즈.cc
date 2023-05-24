#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define pii pair<int,int>

int dr[] = { 0,0,-1,1 };
int dc[] = { -1,1,0,0 };

int n, m;
int cheeseCount = 0;
array<array<int, 100>, 100> board;
array<array<bool, 100>, 100> visit;
queue<pii> q;
vector<pii> meltingCheeses;

bool IsInside(int r, int c);
void BFS();
void MeltCheeses();

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	// 입력받기
	cin >> n >> m;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> board[r][c];

			if (board[r][c] == 1) {
				++cheeseCount;
			}

			// 공기가 있는 부분을 큐에 넣는다.
			if (r == 0 || r == n - 1 || c == 0 || c == m - 1) {
				q.emplace(r, c);
			}
		}
	}

	
	int t = 0;
	int prevCheeseCount = cheeseCount;
	while (true) {
		// 공기를 BFS로 외부 녹는 치즈들을 찾는다.
		BFS();
		// 치즈를 녹이고 큐에 치즈롤 녹이고 생긴 공간들을 추가한다.
		MeltCheeses();

		++t;

		if (cheeseCount == 0)
			break;
		else
			prevCheeseCount = cheeseCount;
	}
	
	cout << t << "\n" << prevCheeseCount;

}

void BFS() {
	while (!q.empty()) {
		auto [r, c] = q.front();
		q.pop();

		for (int i = 0; i < 4; ++i) {
			int nr = r + dr[i];
			int nc = c + dc[i];

			if (!IsInside(nr, nc) || visit[nr][nc])
				continue;

			// 주변타일이 치즈일 경우
			if (board[nr][nc] == 1) {
				meltingCheeses.emplace_back(nr, nc);
			}
			// 공기일 경우
			else if (board[nr][nc] == 0) {
				q.emplace(nr, nc);
			}

			// 방문처리를 한다.
			visit[nr][nc] = true;
		}
	}
}

void MeltCheeses() {
	for (auto [r, c] : meltingCheeses) {
		board[r][c] = 0;
		q.emplace(r, c);
	}
	cheeseCount -= meltingCheeses.size();
	meltingCheeses.clear();
}

bool IsInside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}