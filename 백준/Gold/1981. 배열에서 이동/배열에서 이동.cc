#include <iostream>
#include <array>
#include <algorithm>
#include <queue>
#include <memory.h>

#define MAXN 100

using namespace std;

int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0, 1,-1 };

int n;

array<array<int, MAXN>, MAXN> board;
array<array<bool, MAXN>, MAXN> visit;

bool Goal(int maxDiff);
bool BFS(int bottom, int top);
bool Inside(int x, int y);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> board[j][i];	// x, y
		}
	}

	//문제해결
	int s = 0, e = 200;
	while (s < e) {
		int mid = (s + e) / 2;
		if (Goal(mid))
			e = mid;
		else
			s = mid + 1;
	}
	
	//출력
	cout << s;

}

bool Goal(int maxDiff) {
	// maxDiff만큼 차이나는 범위들을 모두 BFS돌려본다.

	int range[2]{ board[0][0], board[n - 1][n - 1] };
	sort(range, range + 2);

	int top = range[1], bottom = top - maxDiff;
	if (bottom < 0) {	// 필요없는 범위들 최소화 (하한이 0보다 작은경우 제거)
		top -= bottom;
		bottom = 0;
	}

	while (bottom <= range[0] && top <= 200) {

		if (BFS(bottom, top))
			return true;

		++top;
		++bottom;
	}
	return false;
}

bool BFS(int bottom, int top) {
	memset(&visit[0][0], 0, sizeof(visit));

	queue<pair<int,int>> q;
	q.push({ 0,0 });
	visit[0][0] = true;

	while (!q.empty()) {
		auto [x, y] = q.front();	// [,]를 이용해서 pair<>값 받아오기
		q.pop();

		if (x == n - 1 && y == n - 1) {
			return true;
		}

		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (!Inside(nx, ny) || visit[nx][ny])
				continue;

			if (board[nx][ny] < bottom || top < board[nx][ny])
				continue;

			q.push({ nx, ny });
			visit[nx][ny] = true;
		}
	}

	return false;

}

bool Inside(int x, int y) {
	if (x < 0 || n <= x || y < 0 || n <= y)
		return false;
	return true;
}
