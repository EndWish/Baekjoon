#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

int a, b;

int GetSum(int end);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> a >> b;

	//문제해결
	cout << GetSum(b) - GetSum(a - 1);

	//출력

}

int GetSum(int end) {
	int ans = 0;
	int cnt = 1;
	while (end > 0) {
		ans += cnt * min(cnt, end);
		end -= cnt++;
	}

	return ans;
}
