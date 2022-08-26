#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <cmath>
//#include <format>

using namespace std;

string s;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	

	while (true) {
		getline(cin, s);
		//초기화,입력값 받기
		if (s == "#")
			break;

		//문제해결
		int ans = 0;
		ans += ranges::count(s, 'a');
		ans += ranges::count(s, 'e');
		ans += ranges::count(s, 'i');
		ans += ranges::count(s, 'o');
		ans += ranges::count(s, 'u');
		ans += ranges::count(s, 'A');
		ans += ranges::count(s, 'E');
		ans += ranges::count(s, 'I');
		ans += ranges::count(s, 'O');
		ans += ranges::count(s, 'U');

		//출력
		cout << ans << "\n";
	}



}