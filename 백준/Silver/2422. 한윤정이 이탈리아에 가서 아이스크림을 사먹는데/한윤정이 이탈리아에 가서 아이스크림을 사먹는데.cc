#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

array<array<array<unsigned char, 201>, 201>, 201> visit;
int n, m;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> m;
	int input1, input2;
	for (int i = 0; i < m; ++i) {
		cin >> input1 >> input2;
		for (int other = 1; other <= n; ++other) {
			array<int, 3> iceCream{ input1, input2, other };
			sort(iceCream.begin(), iceCream.end());
			visit[iceCream[0]][iceCream[1]][iceCream[2]] = true;
		}
	}

	//문제해결
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			for (int k = j + 1; k <= n; ++k) {
				if (!visit[i][j][k])
					++ans;
			}
		}
	}
	
	//출력
	cout << ans;

}