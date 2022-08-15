#include <iostream>
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <span>
//#include <format>

#define INF numeric_limits<int>::max()
#define MAX 1002
#define pii pair<int,int>

using namespace std;

int n;
int c[MAX][MAX], f[MAX][MAX], visit[MAX];
vector<int> edge[MAX];

int main() 
{

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	int s = 0, e = n + n + 1;

	int input;
	for (int i = 1; i <= n; ++i) {
		cin >> input;
		edge[s].push_back(i);	// 정방향
		c[0][i] = input;
		edge[i].push_back(s);	// 역방향
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			edge[i].push_back(j + n);
			c[i][j + n] = 1;
			edge[j + n].push_back(i);
		}
	}
	for (int i = 1; i <= n; ++i) {
		cin >> input;
		edge[i + n].push_back(e);
		c[i + n][e] = input;
		edge[e].push_back(i + n);
	}

	//문제해결
	while (true) {
		ranges::fill(span(visit), -1);

		//BFS
		queue<int> q;
		q.push(s);
		while (!q.empty()) {
			int x = q.front();
			q.pop();
			//cout << x << "방문 : ";

			for (int i = 0; i < edge[x].size(); ++i) {
				int y = edge[x][i];
				if (visit[y] != -1 || c[x][y] - f[x][y] == 0) {	// 이미 방문한 노드 또는 더이상 흘리수 없을 경우
					continue;
				}
				visit[y] = x;
				q.push(y);
				//cout << y << " ";
				// 만약 e에 도착 했을 경우 돌아가면서 흐를 수 있는 최소값을 찾고 다시 돌오오면서 
				if (y == e)
					break;
			}
			//cout << "\n";
		}
		if (visit[e] == -1)	// 더이상 채울수 없는 경우
			break;

		int node = e;
		int flow = INF;
		while (node != s) {
			flow = min(flow, c[visit[node]][node] - f[visit[node]][node]);
			node = visit[node];
		}
		node = e;
		while (node != s) {
			f[visit[node]][node] += flow;
			f[node][visit[node]] -= flow;
			node = visit[node];
		}
	}

	//출력
	for (int i = 1; i <= n; ++i) {
		if (c[0][i] != f[0][i] || c[n + i][e] != f[n + i][e]) {
			cout << -1;
			return 0;
		}
	}

	cout << 1 << "\n";
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << f[i][j + n];
		}
		cout << "\n";
	}

}