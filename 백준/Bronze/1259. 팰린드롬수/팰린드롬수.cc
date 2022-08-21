#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

int main() 
{

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	bool isP;
	string str;
	while (true) {
		cin >> str;
		if (str == "0") {
			break;
		}

		isP = true;
		
		for (int i = 0; i < str.size() / 2; ++i) {
			if (str[i] != str[str.size() - 1 - i]) {
				isP = false;
				break;
			}
		}
		if (isP) {
			cout << "yes\n";
		}
		else {
			cout << "no\n";
		}
	}

	//문제해결

	//출력

}