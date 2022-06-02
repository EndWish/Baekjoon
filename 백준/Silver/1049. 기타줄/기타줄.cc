#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, m;
int cost[2]{1000, 1000};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	int input1, input2;

	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		cin >> input1 >> input2;
		cost[0] = min(cost[0], input1);	// 6개짜리
		cost[1] = min(cost[1], input2);	// 1개짜리
	}

	//문제해결
	int ans = min({ (n / 6) * cost[0] + (n % 6) * cost[1], (n / 6 + 1) * cost[0] ,n * cost[1] });

	//출력
	cout << ans;

}