#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int dr[] = { 0,0,1, -1 };
int dc[] = { 1, -1,0,0 };

int n, m, k;
array<array<int, 100>, 100> board;
array<array<bool, 100>, 100> visit;

int DFS(int r, int c);
bool IsInside(int r, int c);
void Print();

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m >> k;
	for (int i = 0; i < k; ++i) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		for (int x = x1; x < x2; ++x) {
			for (int y = y1; y < y2; ++y) {
				board[y][x] = 1;
			}
		}
	}

	//Print();
	vector<int> areas;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			if (board[r][c] == 0 && !visit[r][c]) {
				areas.push_back(DFS(r, c));
				//Print();
			}
		}
	}

	ranges::sort(areas);
	cout << areas.size() << "\n";
	for (int area : areas)
		cout << area << " ";

}

int DFS(int r, int c) {
	visit[r][c] = true;

	int result = 1;
	for (int i = 0; i < 4; ++i) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (IsInside(nr, nc) && board[nr][nc] == 0 && !visit[nr][nc])
			result += DFS(nr, nc);
	}

	return result;
}

bool IsInside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}

void Print() {
	cout << "\n";
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			if (board[r][c] == 0) {
				if (!visit[r][c])
					cout << 0 << " ";
				else
					cout << 2 << " ";
			}
			else {
				cout << 1 << " ";
			}
		}
		cout << "\n";
	}

}