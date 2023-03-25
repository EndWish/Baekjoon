#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <cmath>

using namespace std;

#define ll long long
#define pll pair<ll,ll>

int dr[] = { 0,0,-1,1 };
int dc[] = { -1,1,0,0 };

int n, student;
array<array<int, 4>, 401> friends;
array<array<int, 20>, 20> board;

bool IsInside(int r, int c);
int GetScore(int r, int c, int student);
int GetSatisfaction();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	for (int i = 1; i <= n * n; ++i) {
		cin >> student;
		for (int j = 0; j < 4; ++j)
			cin >> friends[student][j];

		int maxR = -1, maxC = -1, maxScore = -1;
		for (int r = 0; r < n; ++r) {
			for (int c = 0; c < n; ++c) {
				if (board[r][c] != 0)
					continue;

				int score = GetScore(r, c, student);
				if (board[r][c] == 0 && maxScore < score) {
					maxR = r;
					maxC = c;
					maxScore = score;
				}
			}
		}

		board[maxR][maxC] = student;
	}
	
	cout << GetSatisfaction();
}

bool IsInside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < n;
}

int GetScore(int r, int c, int student) {
	int score = 0;
	for (int i = 0; i < 4; ++i) {
		int nr = r + dr[i];
		int nc = c + dc[i];
		if (!IsInside(nr, nc))
			continue;
		
		// 빈칸일 경우
		if (board[nr][nc] == 0) {
			score += 1;
			continue;
		}

		// 좋아하는 학생일 경우
		for (int j = 0; j < 4; ++j) {
			if (board[nr][nc] == friends[student][j]) {
				score += 5;
				break;
			}
		}
	}

	return score;
}

int GetSatisfaction() {
	int satisfaction = 0;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			int student = board[r][c];
			int nFriends = 0;
			for (int i = 0; i < 4; ++i) {
				int nr = r + dr[i];
				int nc = c + dc[i];

				if (!IsInside(nr, nc))
					continue;

				for (int j = 0; j < 4; ++j) {
					if (board[nr][nc] == friends[student][j]) {
						++nFriends;
						break;
					}
				}
			}

			satisfaction += int(pow(10, nFriends - 1));
		}
	}
	return satisfaction;
}
