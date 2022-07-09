#include <iostream>
#include <vector>
#include <queue>

#define MAXN 32'001

using namespace std;

int n, m;
vector<int> nextProblem[MAXN];
int preProblemNum[MAXN];

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> m;
	int input1, input2;
	for (int i = 0; i < m; ++i) {
		cin >> input1 >> input2;
		nextProblem[input1].push_back(input2);
		++preProblemNum[input2];
	}

	//문제해결
	priority_queue<int> pq;
	for (int i = 1; i <= n; ++i) {
		if (preProblemNum[i] == 0)
			pq.push(-i);
	}

	while (!pq.empty()) {
		int x = -pq.top();
		pq.pop();

		for (int i = 0; i < nextProblem[x].size(); ++i) {
			int y = nextProblem[x][i];
			if (--preProblemNum[y] == 0)
				pq.push(-y);
		}

		cout << x << " ";
	}

	//출력

}
