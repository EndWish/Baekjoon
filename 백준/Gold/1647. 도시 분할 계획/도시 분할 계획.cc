#include <iostream>
#include <queue>
#include <vector>
#include <numeric>

// 1647

using namespace std;

int n, m;
vector<pair<int, int>> edge[1'000'001];	// 비용, 건너편 집

int Prim();

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> m;
	int a, b, c;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> c;
		edge[a].emplace_back(c, b);
		edge[b].emplace_back(c, a);
	}

	//문제해결
	cout << Prim();

	//출력

}

int Prim() 
{
	vector<int> visit(n + 1, -1);

	priority_queue<pair<int, int>> pq;
	pq.emplace(-0, 1);	// 1번 집부터 있다.
	while (!pq.empty()) {
		auto [curCost, curCity] = pq.top();	
		curCost *= -1;
		
		pq.pop();

		if (visit[curCity] != -1)	// 방문 처리가 됐을 경우 건너뛴다.
			continue;

		//방문처리를 하고, 연결된 간선들을 pq에 삽입한다.
		visit[curCity] = curCost;
		for (int i = 0; i < edge[curCity].size(); ++i) {
			auto [nextCost, nextCity] = edge[curCity][i];

			if (visit[nextCity] != -1)	// 방문 처리가 됐을 경우 건너뛴다.
				continue;

			pq.emplace(-nextCost, nextCity);
		}
	}

	return reduce(visit.begin() + 1, visit.end()) - *max_element(visit.begin() + 1, visit.end());

}
