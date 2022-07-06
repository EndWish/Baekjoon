#include <iostream>
#include <string>

using namespace std;


int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	int ans = 0;
	string buffer;
	while (cin >> buffer)
		++ans;

	//문제해결

	//출력
	cout << ans;

}