#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <numeric>
#include <algorithm>

using namespace std;

int dx[] = { 1,-1,0,0 };
int dy[] = { 0,0,1,-1 };

int n, m;
array<array<char, 50>, 50> board;
array<array<int, 50>, 50> visit;
vector<pair<int, int>> points;
vector<vector<int>> dist;

bool Inside(int x, int y);
int BFS(const pair<int, int>& s, const pair<int, int>& e);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	pair<int, int> start, end;
	cin >> n >> m;
	for (int y = 0; y < m; ++y){
		for (int x = 0; x < n; ++x) {
			cin >> board[x][y];

			if (board[x][y] == 'S') {
				start = { x,y };
				board[x][y] = '.';
			}
			else if (board[x][y] == 'E') {
				end = { x,y };
				board[x][y] = '.';
			}
			else if (board[x][y] == 'X') {
				points.emplace_back(x, y);
				board[x][y] = '.';
			}
		}
	}
	points.insert(points.begin(), start);
	points.push_back(end);

	dist.assign(points.size(), vector<int>(points.size()));

	//문제해결
	// 각 지점에서 다른 지점까지의 거리를 계산한다.
	for (int i = 0; i < points.size(); ++i) {
		dist[i][i] = 0;
		for (int j = i + 1; j < points.size(); ++j) {
			dist[i][j] = BFS(points[i], points[j]);
			dist[j][i] = dist[i][j];
		}
	}

	// 가능한 모든 경로들의 거리를 계산하여 가장 빠른것을 찾는다. (DP와 bitMasking을 사용하면 더빠르게 가능하겠지만 이문제에서 최대5! 이니 그냥한다.)
	vector<int> path(points.size());	
	iota(path.begin(), path.end(), 0);
	int ans = numeric_limits<int>::max();
	do {
		int pathDistance = 0;
		for (int i = 0; i < path.size() - 1; ++i) {
			pathDistance += dist[path[i]][path[i + 1]];
		}
		ans = min(ans, pathDistance);
	} while (next_permutation(path.begin() + 1, path.end() - 1));
	
	//출력
	cout << ans;

}

bool Inside(int x, int y) 
{
	if (x < 0 || n <= x || y < 0 || m <= y)
		return false;
	return true;
}

int BFS(const pair<int, int>& s, const pair<int, int>& e) 
{
	fill_n(&visit[0][0], 50 * 50, -1);

	queue<pair<int, int>> q;
	q.push(s);
	visit[s.first][s.second] = 0;
	while (!q.empty()) {
		auto [x, y] = q.front();
		q.pop();

		if (e == make_pair(x, y)) {	//도착점에 도달했을 경우
			return visit[x][y];
		}
		
		for (int i = 0; i < 4; ++i) {	// 다음 칸으로 이동
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (!Inside(nx, ny) || board[nx][ny] == '#' || 0 <= visit[nx][ny] )
				continue;
			
			q.emplace(nx, ny);
			visit[nx][ny] = visit[x][y] + 1;
		}
		;
	}

	return visit[e.first][e.second];
}
