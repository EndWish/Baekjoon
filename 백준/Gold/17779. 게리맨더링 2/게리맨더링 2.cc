#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define pii pair<int,int>
#define MAXN 20

int dr[] = {  -1, 0, 1, 0, };
int dc[] = { 0, 1, 0, -1, };

int n;
array<array<int, MAXN>, MAXN> board, area;

int SetArea(int sr, int sc);
void MakeBorder(array<pii, 4>& points);
void BFS(int sr, int sc, int num);
int GetDiff();

bool IsInside(pii point);
bool IsInside(int r, int c);

void Print() {
	// 임시
	cout << "\n";
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			cout << area[r][c] << " ";
		}
		cout << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			cin >> board[r][c];
		}
	}
	
	//문제해결
	int ans = numeric_limits<int>::max();
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			ans = min(ans, SetArea(r, c));
		}
	}

	cout << ans;
}

int SetArea(int sr, int sc) {
	int ans = numeric_limits<int>::max();

	int d1 = 1, d2 = 1;
	array<pii, 4> points;
	points[0] = { sr, sc };
	while (true) {
		d2 = 1;

		points[1] = { sr + d1, sc + d1 };
		if (!IsInside(points[1]))
			break;

		while (true) {
			points[2] = { sr + d1 + d2, sc + d1 - d2 };
			points[3] = { sr + d2, sc - d2 };
			if (!IsInside(points[2]) || !IsInside(points[3]))
				break;

			
			ranges::fill_n(&area[0][0], MAXN * MAXN, 0);
			// 경계를 만든다.
			MakeBorder(points);

			// 구역을 채운다.
			BFS(0, 0, 1);
			BFS(0, n - 1, 2);
			BFS(n - 1, n - 1, 3);
			BFS(n - 1, 0, 4);

			pii startPoint = points[0];
			while (startPoint != points[1]) {
				BFS(startPoint.first + 1, startPoint.second, 5);
				startPoint.first += 1;
				startPoint.second += 1;
			}
			startPoint = points[0];
			while (startPoint != points[3]) {
				BFS(startPoint.first + 1, startPoint.second, 5);
				startPoint.first += 1;
				startPoint.second -= 1;
			}

			// 구역 출력 테스트
			//if (GetDiff() < ans)
			//	Print();

			// 가장큰 인구차이를 구해서 답을 갱신해준다.
			ans = min(ans, GetDiff());

			

			++d2;
		}
		++d1;
	}

	return ans;
}

void MakeBorder(array<pii, 4>& points) {
	static int dr2[] = {  1,1,-1,-1, };
	static int dc2[] = { 1,-1,-1,1, };

	for (int i = 0; i < 4; ++i) {
		pii startPoint = points[i];
		pii endPoint = points[(i + 1) % 4];
		while (startPoint != endPoint) {
			area[startPoint.first][startPoint.second] = 5;
			startPoint.first += dr2[i];
			startPoint.second += dc2[i];
		}
	}

	for (int i = 0; i < 4; ++i) {
		pii startPoint = points[i];
		while (true) {
			startPoint.first += dr[i];
			startPoint.second += dc[i];
			if (!IsInside(startPoint))
				break;

			area[startPoint.first][startPoint.second] = i + 1;
		}
	}

}

void BFS(int sr, int sc, int num) {
	queue<pii> q;
	q.emplace(sr, sc);
	area[sr][sc] = num;
	while (!q.empty()) {
		auto[r, c] = q.front();
		q.pop();

		for (int i = 0; i < 4; ++i) {
			int nr = r + dr[i];
			int nc = c + dc[i];
			if (IsInside(nr, nc) && area[nr][nc] == 0) {
				area[nr][nc] = num;
				q.emplace(nr, nc);
			}
		}
	}
}

int GetDiff() {
	array<int, 6> sums;
	sums.fill(0);
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			sums[area[r][c]] += board[r][c];
		}
	}

	int maxSum = *ranges::max_element(sums.begin() + 1, sums.end());
	int minSum = *ranges::min_element(sums.begin() + 1, sums.end());

	return maxSum - minSum;
}

bool IsInside(pii point) {
	return IsInside(point.first, point.second);
}
bool IsInside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < n;
}
