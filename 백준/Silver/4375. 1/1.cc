#include <iostream>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define ll  long long

int n;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	while (cin >> n) {
		//초기화,입력값 받기

		//문제해결
		int ans = 1;
		int num = 1;
		while (true) {
			num %= n;
			if (num == 0) {
				cout << ans << "\n";
				break;
			}
			else {
				num = num * 10 + 1;
				++ans;
			}
		}

		//출력

	}


}
