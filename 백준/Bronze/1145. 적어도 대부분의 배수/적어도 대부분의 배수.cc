#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

array<int, 5> arr;

int GCD(int a, int b);
int LCM(int a, int b);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	for (int& n : arr)
		cin >> n;

	//문제해결

	// 방법1. 0~1000000까지 돌면서 3가지 이상의 수로 나누어지는지 확인 (N^3)
	// 방법2. 5개중 3개를 골라 최소공배수를 구한다. 최소공배수중 가장 작은것이 답. O(3NlogN)
	int ans = 1000000;
	for (int i = 0; i <= 2; ++i) {
		for (int j = i + 1; j <= 3; ++j) {
			for (int k = j + 1; k <= 4; ++k) {
				ans = min(ans, LCM(LCM(arr[i], arr[j]), arr[k]));
			}
		}
	}

	//출력
	cout << ans;

}

int GCD(int a, int b) {
	if (b == 0)
		return a;
	return GCD(b, a % b);
}

int LCM(int a, int b) {
	if (a < b)
		swap(a, b);

	return a * b / GCD(a, b);
}