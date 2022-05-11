#include <iostream>
#include <array>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	char c;
	int ans = 0;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			cin >> c;
			if (c == 'F' && !((i + j)&1) ) {
				++ans;
			}
		}
	}

	//문제해결

	//출력
	cout << ans;
}