#include <iostream>
#include <algorithm>

#define ll long long

using namespace std;

ll a, b;

ll OneNumOfZeroToN(ll n);
ll OneNumOfN(ll n);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> a >> b;

	//문제해결
	

	//출력
	cout << OneNumOfZeroToN(b) - OneNumOfZeroToN(a - 1);

}

ll OneNumOfZeroToN(ll n) 
{
	/*	각 자리수마다 특정 방식으로 반복되는 성질을 이용하여 개수를 셈
	1의 자리 : 0 1 0 1 0 1 0 1 0 .... 
	2의 자리 : 0 0 1 1 0 0 1 1 0 ....
	3의 자리 : 0 0 0 0 1 1 1 1 0 ....
	*/

	ll res = 0;

	ll div = 2;
	ll operand = n + 1;
	while (div / 2 <= n) {
		res += (operand / div) * (div / 2);
		res += max(0LL, operand % div - div / 2);
		div *= 2;
	}
	//cout << "0-" << n << " : " << res << "\n";
	return res;
}