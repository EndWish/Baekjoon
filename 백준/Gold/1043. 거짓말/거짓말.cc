#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

int n, m;
vector<int> edge[51];
vector<vector<int>> parties;
bool truth[51];

void DFS(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	int startNum;
	cin >> startNum;
	vector<int> start(startNum);
	for (int& i : start)
		cin >> i;

	int num;
	for (int i = 0; i < m; ++i) {
		cin >> num;
		vector<int> party(num);
		for (int& p : party)
			cin >> p;

		for (int j = 0; j < party.size(); ++j) {
			for (int k = j + 1; k < party.size(); ++k) {
				edge[party[j]].push_back(party[k]);
				edge[party[k]].push_back(party[j]);
			}
		}

		parties.push_back(move(party));
	}

	//문제해결
	for (int s : start) {
		if (!truth[s])
			DFS(s);
	}

	int ans = 0;
	for (const vector<int>& party : parties) {
		if (!truth[party[0]])
			++ans;
	}

	//출력
	cout << ans;

}

void DFS(int node) {
	truth[node] = true;
	for (int i = 0; i < edge[node].size(); ++i) {
		int nextNode = edge[node][i];
		if (!truth[nextNode]) {
			DFS(nextNode);
		}
	}
}
