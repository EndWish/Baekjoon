#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXN 50
#define pii pair<int,int>

int dr[] = { 0, -1, 0, 1 };
int dc[] = { -1, 0, 1, 0 };

int n, m;
array<array<array<bool, 4>, MAXN>, MAXN> walls;
array<array<pii, MAXN>, MAXN> parents;
array<array<int, MAXN>, MAXN> roomSize;

array<array<bool, MAXN>, MAXN> visit;

bool IsInside(int r, int c);
pii Find(int r, int c);
void Unite(int r1, int c1, int r2, int c2);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	ranges::fill_n(&roomSize[0][0], MAXN * MAXN, 1);

	int input;
	cin >> n >> m;
	for (int r = 0; r < m; ++r) {
		for (int c = 0; c < n; ++c) {
			cin >> input;
			for (int i = 0; i < 4; ++i) {
				if (input & (1 << i))
					walls[r][c][i] = true;
			}
			parents[r][c] = { r, c };
		}
	}
	
	for (int r = 0; r < m; ++r) {
		for (int c = 0; c < n; ++c) {
			// 옆에 있는방과 이어져 있다면 연결한다.
			for (int i = 0; i < 4; ++i) {
				int nr = r + dr[i];
				int nc = c + dc[i];
				if (!walls[r][c][i] && IsInside(nr, nc)) {
					Unite(r, c, nr, nc);
				}
			}

		}
	}

	int nRoom = 0, maxRoomSize = 1, maxMergeRoomSize = 1;
	for (int r = 0; r < m; ++r) {
		for (int c = 0; c < n; ++c) {
			pii parentPos = Find(r, c);
			if (!visit[parentPos.first][parentPos.second]) {
				visit[parentPos.first][parentPos.second] = true;
				++nRoom;
				maxRoomSize = max(maxRoomSize, roomSize[parentPos.first][parentPos.second]);
			}

			// 옆에 있는방과 이어져 있다면 연결한다.
			for (int i = 0; i < 4; ++i) {
				int nr = r + dr[i];
				int nc = c + dc[i];
				if (walls[r][c][i] && IsInside(nr, nc)) {
					pii nextParentPos = Find(nr, nc);
					if (parentPos != nextParentPos) {
						int mergeRoomSize = roomSize[parentPos.first][parentPos.second] + roomSize[nextParentPos.first][nextParentPos.second];
						maxMergeRoomSize = max(maxMergeRoomSize, mergeRoomSize);
					}
				}
			}

		}
	}

	cout << nRoom << "\n";
	cout << maxRoomSize << "\n";
	cout << maxMergeRoomSize << "\n";

}

pii Find(int r, int c) {
	pii pos = { r, c };
	if (parents[r][c] == pos)
		return pos;
	return parents[r][c] = Find(parents[r][c].first, parents[r][c].second);
}

void Unite(int r1, int c1, int r2, int c2) {
	pii pos1 = { r1, c1 };
	pii pos2 = { r2, c2 };
	pos1 = Find(pos1.first, pos1.second);
	pos2 = Find(pos2.first, pos2.second);
	if (pos1 == pos2)
		return;

	if (pos1 > pos2)
		swap(pos1, pos2);

	roomSize[pos1.first][pos1.second] += roomSize[pos2.first][pos2.second];
	roomSize[pos2.first][pos2.second] = 0;
	parents[pos2.first][pos2.second] = pos1;
}

bool IsInside(int r, int c) {
	return 0 <= r && r < m && 0 <= c && c < n;
}


