#include <iostream>
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

int a, b;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	while (true) {
		//초기화,입력값 받기
		cin >> a >> b;
		if (a == 0 && b == 0)
			break;

		//문제해결
		if (a > b)
			cout << "Yes\n";
		else
			cout << "No\n";

		//출력
	}



}