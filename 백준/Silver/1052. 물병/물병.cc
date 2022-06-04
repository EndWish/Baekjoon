#include <iostream>

using namespace std;

int n, k;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기

	cin >> n >> k;
	//문제해결
	for (int i = 0; i < k - 1; ++i) {	// k-1번 합칠수 있는 만큼 합친다.
		
		int water = 1;
		while (water <= n) {
			water *= 2;
		}
		water /= 2;	// while문을 돌고나면 n보다 커지기 때문에 2로 나눈다.

		n -= water;

		if (n == 0) {
			cout << 0;
			return 0;
		}
	}
	
	// k번째에서 넘치는 만큼 물을 사온다.
	int water = 1;
	while (water < n) {
		water *= 2;
	}

	//출력
	cout << water - n;

}