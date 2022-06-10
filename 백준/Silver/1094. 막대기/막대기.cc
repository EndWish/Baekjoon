#include <iostream>

using namespace std;

int x;

int CountOneBit(int num);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> x;

	//문제해결

	//출력
	cout << CountOneBit(x);

}

int CountOneBit(int num) {
	int cnt = 0;
	while (num) {
		num &= (num - 1);
		++cnt;
	}
	return cnt;
}
