#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

//1507

using namespace std;

int n;
vector<vector<int>> dist;
vector<vector<bool>> edge;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;
	dist.assign(n, vector<int>(n, 0));
	for (auto& r : dist)
		for (int& c : r)
			cin >> c;

	edge.assign(n, vector<bool>(n, true));
	//문제해결
	
	// 1. 간선의 정보 찾기

	for (int k = 0; k < n; ++k) {
		for (int r = 0; r < n; ++r) {
			if (k == r)
				continue;

			for (int c = 0; c < n; ++c) {
				if (k == c || r == c)
					continue;

				if (dist[r][c] > dist[r][k] + dist[k][c]) {	// 최단거리가 더 클수는 없다. 
					std::cout << -1;
					return 0;
				}
				else if (dist[r][c] == dist[r][k] + dist[k][c]) {	// 경유했을때가 최단거리라면 직통 거리를 만들 필요가 없다.
					edge[r][c] = false;
				}
			}
		}
	}

	// 2. 거리의 합 구하기
	int ans = 0;
	for (int r = 0; r < n; ++r)
		for (int c = r + 1; c < n; ++c)
			if (edge[r][c])
				ans += dist[r][c];
	
	//출력
	cout << ans;

}
