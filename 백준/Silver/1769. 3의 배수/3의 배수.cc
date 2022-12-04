#include <iostream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

string x;

string Transform(string num);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> x;

	//문제해결
	int ans = 0;
	while (2 <= x.size()) {
		x = Transform(x);
		++ans;
	}

	//출력
	cout << ans << "\n";
	if (x[0] % 3 == 0) {
		cout << "YES";
	}
	else {
		cout << "NO";
	}

}

string Transform(string num) {
	int sum = 0;
	for (char c : num)
		sum += c - '0';

	string result;
	while (0 < sum) {
		result.push_back(sum % 10 + '0');
		sum /= 10;
	}
	return result;
}
