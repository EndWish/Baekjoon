#include <iostream>
#include <string>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

string s1, s2;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> s1 >> s2;

	//문제해결
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < s1.size(); ++j) {
			bool num[2] = { s1[j] - '0', s2[j] - '0' };

			switch (i) {
			case 0:
				cout << (num[0] & num[1]);
				break;
			case 1:
				cout << (num[0] | num[1]);
				break;
			case 2:
				cout << (num[0] ^ num[1]);
				break;
			case 3:
				cout << (!num[0]);
				break;
			case 4:
				cout << (!num[1]);
				break;
			default:
				break;
			}

		}
		cout << "\n";
	}

	//출력


}
