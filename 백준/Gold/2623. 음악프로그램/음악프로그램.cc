#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
vector<int> preNum;
vector<vector<int>> graph;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> m;
	preNum.assign(n + 1, 0);
	graph.assign(n + 1, vector<int>{});

	int num;
	int s, e;
	for (int i = 0; i < m; ++i) {
		cin >> num;
		cin >> s;
		for (int j = 1; j < num; ++j) {
			cin >> e;
			graph[s].push_back(e);
			++preNum[e];
			s = e;
		}
	}

	//문제해결
	vector<int> ans;
	ans.reserve(n);

	queue<int> q;
	for (int singer = 1; singer <= n; ++singer) {
		if (preNum[singer] == 0) {
			q.push(singer);
			//cout << "push : " << singer << "\n";
		}
		
	}


	while (!q.empty()) {
		int x = q.front();
		q.pop();
		//cout << "pop : " << x << "\n";
		ans.push_back(x);

		for (int singer : graph[x]) {
			if (--preNum[singer] == 0) {
				q.push(singer);
				//cout << "push : " << singer << "\n";
			}
		}	

	}


	
	//출력
	if (ans.size() == n) {
		for (int singer : ans)
			cout << singer << "\n";
	}
	else {
		cout << "0";
	}

}