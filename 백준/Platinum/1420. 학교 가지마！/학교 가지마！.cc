#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define MAXN 100
#define MAXNN (MAXN * MAXN)
#define pii pair<int,int>

struct Edge {
	int flow, capacity;

	Edge() {
		flow = 0;
		capacity = 0;
	}
	Edge(int _flow, int _capacity) : flow{ _flow }, capacity{ _capacity }{

	}
};

int dr[4] = { 1, -1, 0,0 };
int dc[4] = { 0,0, 1, -1 };

int n, m, s, t;
array<array<char, MAXN>, MAXN> board;
array<unordered_map<int, Edge>, MAXNN * 2> edges;

int Input(int x);
int Output(int x);
bool Inside(int r, int c);
int Edmonds_Karp();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			cin >> board[r][c];
		}
	}

	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < m; ++c) {
			if (board[r][c] == '#')
				continue;

			if (board[r][c] == 'K')
				s = Output(c + r * m);
			else if (board[r][c] == 'H')
				t = Input(c + r * m);

			edges[Input(c + r * m)].emplace(Output(c + r * m), Edge(0, 1));
			edges[Output(c + r * m)].emplace(Input(c + r * m), Edge(0, 0));

			for (int i = 0; i < 4; ++i) {
				int nr = r + dr[i];
				int nc = c + dc[i];
				if (Inside(nr, nc) && board[nr][nc] != '#') {
					edges[Output(c + r * m)].emplace(Input(nc + nr * m), Edge(0, 1));

					// 막는 것이 불가능한 경우
					if (board[r][c] == 'K' && board[nr][nc] == 'H') {
						cout << -1;
						return 0;
					}
				}
			}


		}
	}

	
	
	//문제해결
	cout << Edmonds_Karp();

}

bool Inside(int r, int c) {
	return 0 <= r && r < n && 0 <= c && c < m;
}

int Edmonds_Karp() {
	int totalFlow = 0;
	vector<int> visit(MAXNN * 2, -1);

	// 최대유량일 될때 까지 물을 흘려준다.
	while (true) {
		// 물을 흘릴수 있는 경로를 찾는다. (BFS)
		ranges::fill(visit, -1);
		
		queue<int> q;
		q.push(s);
		visit[s] = s;
		while (!q.empty()) {
			int node = q.front();
			q.pop();

			// 도착지에 도착하면 멈춘다.
			if (node == t)
				break;

			for (auto [nextNode, edge] : edges[node]) {
				// 아직 방문하지 않았고 흐를수 있을 경우 방문한다.
				if(visit[nextNode] == -1 && edge.flow < edge.capacity){
					visit[nextNode] = node;
					q.push(nextNode);
				}
			}
		}

		// 더이상 흘릴 수 있는 경로가 없을 경우 그만한다.
		if (visit[t] == -1)
			break;

		// 흘릴수 있는 최대 수량을 찾는다.
		int water = numeric_limits<int>::max();
		for (int node = t; node != s; node = visit[node]) {
			Edge& edge = edges[visit[node]][node];
			water = min(water, edge.capacity - edge.flow);
		}
		// 물을 흘린다.
		totalFlow += water;
		for (int node = t; node != s; node = visit[node]) {
			int preNode = visit[node];
			Edge& edge = edges[preNode][node];
			Edge& reverseEdge = edges[node][preNode];
			edge.flow += water;
			reverseEdge.flow -= water;
		}
	}

	return totalFlow;
}


int Input(int x) {
	return x;
}
int Output(int x) {
	return x + MAXNN;
}