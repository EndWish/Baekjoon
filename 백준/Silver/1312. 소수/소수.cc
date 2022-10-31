#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

int a, b;
int n;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> a >> b >> n;

	//문제해결
	for (int i = 0; i < n; ++i) {
		a %= b;
		a *= 10;
	}

	//출력
	cout << a / b;

}
