#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXN 201

using namespace std;

int n, m;
vector<int> edge[MAXN];
int visit[MAXN];
bool finished[MAXN];

bool DFS(int cow);

int main() 
{

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	int s;
	for (int i = 1; i <= n; ++i) {
		cin >> s;
		edge[i].assign(s, 0);
		for (int& e : edge[i])
			cin >> e;
	}

	//문제해결
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		ranges::fill(finished, false);
		if (DFS(i)) {
			++ans;
		}
	}

	//출력
	cout << ans;

}

bool DFS(int cow) {
	for (int i = 0; i < edge[cow].size(); ++i) {
		int pos = edge[cow][i];
		if (!finished[pos]) {
			finished[pos] = true;
			if (visit[pos] == 0 || DFS(visit[pos])) {
				visit[pos] = cow;
				return true;
			}
		}
	}
	return false;
}
