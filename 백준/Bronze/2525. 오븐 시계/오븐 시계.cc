#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

int a, b, c;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> a >> b >> c;

	//문제해결
	int min = (a * 60 + b + c) % (24*60);

	//출력
	cout << min / 60 << " " << min % 60;

}
