#include <iostream>
#include <vector>
#include <stack>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>



using namespace std;

int n;
vector<int> num1, num2;
vector<int> edge[1001];
int visit[1001];
bool finished[1001];
bool isPrime[2001];

void eratosthenes();
bool DFS(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	int num;
	cin >> num;
	num1.push_back(num);
	for (int i = 1; i < n; ++i) {
		cin >> num;
		if ((num & 1) == (num1[0] & 1))
			num1.push_back(num);
		else
			num2.push_back(num);
	}

	eratosthenes();
	for (auto v1 : num1) {
		for (auto v2 : num2) {
			if (isPrime[v1 + v2]) {
				edge[v1].push_back(v2);
			}
		}
	}

	//문제해결
	vector<int> ans;
	for (auto v2 : num2) {
		if (isPrime[num1[0] + v2]) {
			int matching = 1;
			fill_n(&visit[0], 1001, 0);
			for (auto v1 : num1 | views::drop(1)) {
				fill_n(&finished[0], 1001, false);
				finished[v2] = true;
				if (DFS(v1))
					++matching;
			}
			if (matching == n / 2) {
				ans.push_back(v2);
			}
		}
	}

	//출력
	if (0 < ans.size()) {
		ranges::sort(ans);
		for (auto v : ans)
			cout << v << " ";
	}
	else {
		cout << -1;
	}


}

void eratosthenes() {
	fill_n(&isPrime[0], 2001, true);
	isPrime[0] = false;
	isPrime[1] = false;
	for (int i = 2; i * i <= 2000; ++i) {
		if (isPrime[i]) {	// i가 소수일 경우
			for (int j = i * i; j <= 2000; j += i) {
				isPrime[j] = false;
			}
		}
	}
}

bool DFS(int node) {
	for (int i = 0; i < edge[node].size(); ++i) {
		int nextNode = edge[node][i];
		if (!finished[nextNode]) {
			finished[nextNode] = true;
			if (visit[nextNode] == 0 || DFS(visit[nextNode])) {
				visit[nextNode] = node;
				return true;
			}
		}
	}
	return false;
}