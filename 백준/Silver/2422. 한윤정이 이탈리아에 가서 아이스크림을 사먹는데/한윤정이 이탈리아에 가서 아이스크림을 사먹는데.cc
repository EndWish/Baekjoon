#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

array<array<unsigned char, 201>, 201> visit;
int n, m;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> m;
	int input1, input2;
	for (int i = 0; i < m; ++i) {
		cin >> input1 >> input2;
		if (input1 > input2)
			swap(input1, input2);
		visit[input1][input2] = true;
	}

	//문제해결
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (visit[i][j])
				continue;
			for (int k = j + 1; k <= n; ++k) {
				if (visit[i][k] || visit[j][k])
					continue;
				++ans;
			}
		}
	}
	
	//출력
	cout << ans;

}