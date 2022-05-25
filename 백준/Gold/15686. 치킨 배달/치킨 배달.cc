#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

int n, m;
int ans = numeric_limits<int>::max();

vector<pair<int, int>> chicken;	//r, c
vector<bool> active;
vector<pair<int, int>> home;	// r, c
vector<int> dist;	//치킨거리

void DFS(int index, int nActive);
int GetChickenDistance();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> m;
	chicken.reserve(13);
	home.reserve(2 * n);

	int input;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> input;
			if (input == 1)
				home.emplace_back(i, j);
			else if (input == 2)
				chicken.emplace_back(i, j);
		}
	}

	active.assign(chicken.size(), false);
	dist.assign(home.size(), numeric_limits<int>::max());

	//문제해결
	DFS(0, m);	//인덱스, 남은 활성화 갯수
	
	//출력
	cout << ans;

}

void DFS(int index, int nActive) 
{
	if (index == active.size()) {
		if (nActive == 0) //필요한 만큼 활성화 하지 않음
			ans = min(ans, GetChickenDistance());
		return;
	}

	active[index] = false;
	DFS(index + 1, nActive);

	if (0 < nActive) {
		active[index] = true;
		DFS(index + 1, nActive - 1);
	}
}

int GetChickenDistance() {
	fill(dist.begin(), dist.end(), numeric_limits<int>::max());

	for (int i = 0; i < home.size(); ++i) {
		auto[hr, hc] = home[i];
		for (int j = 0; j < chicken.size(); ++j) {
			if (active[j]) {
				auto[cr, cc] = chicken[j];
				dist[i] = min(dist[i], abs(hr - cr) + abs(hc - cc));
			}
		}
	}

	return reduce(dist.begin(), dist.end());
}
