#include <iostream>
#include <queue>
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

array<array<char, 12>, 6> board;
array<array<bool, 12>, 6> visit;

bool IsInside(int x, int y);
int DFS(int x, int y);
bool Destroy();
void DFSDestroy(int x, int y);
void Move();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	for (int y = 11; 0 <= y ; --y) {
		for (int x = 0; x < 6; ++x) {
			cin >> board[x][y];
		}
	}
	
	int ans = 0;
	while (true) {
		if (!Destroy())
			break;
		++ans;
		Move();
	}
	
	cout << ans;
}

bool Destroy() {
	bool result = false;
	ranges::fill_n(&visit[0][0], 12 * 6, false);
	for (int x = 0; x < 6; ++x) {
		for (int y = 0; y < 12; ++y) {
			if (!visit[x][y] && board[x][y] != '.' && 4 <= DFS(x, y)) {
				DFSDestroy(x, y);
				result = true;
			}
		}
	}

	return result;
}
int DFS(int x, int y) {
	visit[x][y] = true;

	int sum = 1;
	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (IsInside(nx, ny) && !visit[nx][ny] && board[x][y] == board[nx][ny]) {
			sum += DFS(nx, ny);
		}
	}

	return sum;
}
void DFSDestroy(int x, int y) {
	char ch = board[x][y];
	board[x][y] = '.';

	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (IsInside(nx, ny) && ch == board[nx][ny]) {
			DFSDestroy(nx, ny);
		}
	}
}

void Move() {
	for (int x = 0; x < 6; ++x) {
		int targetY = 0;
		for (int y = 0; y < 12; ++y) {
			if (board[x][y] != '.') {
				char ch = board[x][y];
				board[x][y] = '.';
				board[x][targetY++] = ch;
			}
		}
	}
}

bool IsInside(int x, int y) {
	return 0 <= x && x < 6 && 0 <= y && y < 12;
}
