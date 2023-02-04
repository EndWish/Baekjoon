#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int l, a, b, c, d;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> l >> a >> b >> c >> d;

	//문제해결
	cout << l - max((a + c - 1) / c, (b + d - 1) / d);

}
