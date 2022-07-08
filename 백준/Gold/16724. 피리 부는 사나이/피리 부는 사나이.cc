#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

using namespace std;

int n, m;
char board[1000][1000];
int id[1000][1000];
bool visit[1000][1000];
int idCnt;

int DFS(int r, int c);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> m;
	for (int r = 0; r < n; ++r)
		for (int c = 0; c < m; ++c)
			cin >> board[r][c];

	//문제해결
	for (int r = 0; r < n; ++r)
		for (int c = 0; c < m; ++c)
			if(!visit[r][c])	// 방문을 안한 곳이라면 DFS 수행
				DFS(r, c);

	//출력
	cout << idCnt;
}

int DFS(int r, int c) {
	visit[r][c] = true;

	int nr = r;
	int nc = c;
	switch (board[r][c]) {
	case 'D': ++nr; break;
	case 'U': --nr; break;
	case 'R': ++nc; break;
	case 'L': --nc; break;
	default:
		break;
	}

	if (visit[nr][nc]) {	// 방문했을 경우
		if (id[nr][nc] == 0) {	// 처리중일 경우
			id[r][c] = ++idCnt;
		}
		else {
			id[r][c] = id[nr][nc];
		}
	}
	else {	// 방문하지 않았을 경우
		return id[r][c] = DFS(nr, nc);
	}

	return id[r][c];
}
