#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int dr[] = { 0,0,1,-1 };
int dc[] = { 1,-1,0,0 };

int n, m;
array<array<char, 100>, 100> board;
array<array<bool, 100>, 100> visit;

int DFS(int r, int c);
bool IsInside(int r, int c);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	
	cin >> m >> n;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> board[r][c];
		}
	}

	int whitePower = 0;
	int bluePower = 0;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			if (!visit[r][c]) {
				int power = DFS(r, c);
				power *= power;
				if (board[r][c] == 'W')
					whitePower += power;
				else
					bluePower += power;
			}
		}
	}
	
	cout << whitePower << " " << bluePower;

}

int DFS(int r, int c) {
	visit[r][c] = true;

	int result = 1;
	for (int i = 0; i < 4; ++i) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (IsInside(nr, nc) && !visit[nr][nc] && board[r][c] == board[nr][nc]) {
			result += DFS(nr, nc);
		}
	}

	return result;
}

bool IsInside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}