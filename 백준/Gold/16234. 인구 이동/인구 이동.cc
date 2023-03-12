#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <cmath>

using namespace std;

#define MAXN 50
#define pii pair<int,int>

int n, minPopulation, maxPopulation;
array<array<int, MAXN>, MAXN> board;
array<array<pii, MAXN>, MAXN> parent;
array<array<int, MAXN>, MAXN> population, nNation;

void OpenBorder();
void Unite(int r1, int c1, int r2, int c2);
pii Find(int r, int c);
bool IsInside(int r, int c);

void Print();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> minPopulation >> maxPopulation;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			cin >> board[r][c];
		}
	}

	//문제해결
	int ans = 0;
	while (true) {
		// 국경선을 연다
		OpenBorder();

		bool stop = true;
		for (int r = 0; r < n; ++r) {
			for (int c = 0; c < n; ++c) {
				auto [pr, pc] = Find(r, c);
				// 연합국이 1개 보다 많은 경우
				if (1 < nNation[pr][pc]) {
					stop = false;
					board[r][c] = population[pr][pc] / nNation[pr][pc];
				}
			}
		}

		//cout << "\n";
		//Print();

		if (stop)
			break;
		else
			++ans;
	}
	cout << ans;
}

void OpenBorder() {
	// 초기화
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			parent[r][c] = {r, c};
			population[r][c] = board[r][c];
			nNation[r][c] = 1;
		}
	}

	// Unite
	int dr[2] = { 1 ,0 };
	int dc[2] = { 0 ,1 };
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			for (int i = 0; i < 2; ++i) {
				auto [nr, nc] = make_pair(r + dr[i], c + dc[i]);
				if (IsInside(nr, nc) && minPopulation <= abs(board[r][c] - board[nr][nc])
					&& abs(board[r][c] - board[nr][nc]) <= maxPopulation) {
					Unite(r, c, nr, nc);
				}
			}
		}
	}

}

void Unite(int r1, int c1, int r2, int c2) {
	tie(r1, c1) = Find(r1, c1);
	tie(r2, c2) = Find(r2, c2);

	if (make_pair(r1, c1) == make_pair(r2, c2))
		return;

	if (make_pair(r1, c1) > make_pair(r2, c2)) {
		swap(r1, r2);
		swap(c1, c2);
	}

	population[r1][c1] += population[r2][c2];
	population[r2][c2] = 0;
	nNation[r1][c1] += nNation[r2][c2];
	nNation[r2][c2] = 0;
	parent[r2][c2] = {r1, c1};
}

pii Find(int r, int c) {
	if (make_pair(r, c) == parent[r][c])
		return make_pair(r, c);
	return parent[r][c] = Find(parent[r][c].first, parent[r][c].second);
}

bool IsInside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < n;
}

void Print() {
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			cout << board[r][c] << " ";
		}
		cout << "\n";
	}
}
