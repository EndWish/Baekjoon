#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXN 10
#define pii pair<int,int>

int dr[8] = { -1, -1, 0,1,1,1,0,-1 };
int dc[8] = { 0, 1,1,1,0,-1,-1,-1 };

int n, m, k;
array<array<int, MAXN>, MAXN> board, extra;
array<array<vector<int>, MAXN>, MAXN> trees, deadTrees;

void TreesSort();
bool IsInside(int r, int c);

void Spring();
void Summer();
void Autumn();
void Winter();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m >> k;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			board[r][c] = 5;
			cin >> extra[r][c];
		}
	}
	for (int i = 0; i < m; ++i) {
		int x, y, z;
		cin >> x >> y >> z;
		--x; --y;
		trees[x][y].push_back(z);
	}
	TreesSort();
	
	//문제해결
	while (k-- > 0) {
		Spring();
		Summer();
		Autumn();
		Winter();
	}

	int ans = 0;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			ans += trees[r][c].size();
		}
	}
	cout << ans;

}

void Spring() {
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			for (int i = trees[r][c].size() - 1; 0 <= i; --i) {
				int& age = trees[r][c][i];
				if (age <= board[r][c]) {
					board[r][c] -= age;
					++age;
				}
				else {
					// 죽을 나무들을 추가한다.
					deadTrees[r][c].insert(deadTrees[r][c].end(), trees[r][c].begin(), trees[r][c].begin() + i + 1);
					// 나무는 죽는다.
					trees[r][c].erase(trees[r][c].begin(), trees[r][c].begin() + i + 1);
					break;
				}
			}
		}
	}
}
void Summer() {
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			for (int age : deadTrees[r][c]) {
				board[r][c] += age / 2;
			}
			deadTrees[r][c].clear();
		}
	}
}
void Autumn() {
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			for (int age : trees[r][c]) {
				if (age % 5 == 0) {
					for (int i = 0; i < 8; ++i) {
						int nr = r + dr[i];
						int nc = c + dc[i];
						if(IsInside(nr, nc))
							trees[nr][nc].push_back(1);
					}
				}
			}
		}
	}
}
void Winter() {
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			board[r][c] += extra[r][c];
		}
	}
}

bool IsInside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < n;
}

void TreesSort() {
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			ranges::sort(trees[r][c], greater<int>());
		}
	}
}