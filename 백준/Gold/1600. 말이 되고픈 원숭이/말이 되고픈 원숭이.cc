#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <tuple>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define INF numeric_limits<int>::max()
#define t3i tuple<int,int,int>

int dx1[] = { 1,-1,0,0 };
int dy1[] = { 0,0, 1,-1 };
int dx2[] = { 1,2,2,1,-1,-2,-2,-1 };
int dy2[] = { -2,-1,1,2,2,1,-1,-2 };

int k, w, h;
array<array<int, 200>, 200> board;
array<array<array<int, 200>, 200>, 31> visit;

bool Inside(int x, int y);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> k >> w >> h;
	for (int y = 0; y < h; ++y)
		for (int x = 0; x < w; ++x)
			cin >> board[x][y];

	fill_n(&visit[0][0][0], 200 * 200 * 31, -1);

	//문제해결
	queue<t3i> q;
	visit[0][0][0] = 0;
	q.emplace(0,0,0);
	while (!q.empty()) {
		auto [depth, x, y] = q.front();
		q.pop();

		// 상하좌우로 이동
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx1[i];
			int ny = y + dy1[i];
			if (Inside(nx, ny) && board[nx][ny] == 0 && visit[depth][nx][ny] == -1) {	// 보드밖을 나가지 않고, 장애물이 없고, 방문하지 않았을 경우
				visit[depth][nx][ny] = visit[depth][x][y] + 1;
				q.emplace(depth, nx, ny);
			}
		}

		// 말 이동
		if (depth < k) {
			for (int i = 0; i < 8; ++i) {
				int nx = x + dx2[i];
				int ny = y + dy2[i];
				int ndepth = depth + 1;
				if (Inside(nx, ny) && board[nx][ny] == 0 && visit[ndepth][nx][ny] == -1) {	// 보드밖을 나가지 않고, 장애물이 없고, 방문하지 않았을 경우
					visit[ndepth][nx][ny] = visit[depth][x][y] + 1;
					q.emplace(ndepth, nx, ny);
				}
			}
		}

	}

	//출력
	int ans = INF;
	for (int depth = 0; depth <= k; ++depth)
		if(visit[depth][w - 1][h - 1] != -1)
			ans = min(ans, visit[depth][w - 1][h - 1]);
	
	if (ans == INF)
		cout << -1;
	else
		cout << ans;

}

bool Inside(int x, int y) {
	if (x < 0 || w <= x || y < 0 || h <= y)
		return false;
	return true;
}

