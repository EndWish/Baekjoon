#include <iostream>
#include <algorithm>

using namespace std;

int n, a, b;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> a >> b;
	--a;
	--b;

	//문제해결
	int round = 1;
	int people = 2;
	while (people <= n) {
		if (a / people == b / people)
			break;

		++round;
		people *= 2;
	}

	//출력
	cout << round;

}