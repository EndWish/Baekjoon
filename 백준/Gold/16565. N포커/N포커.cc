#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

#define DIV 10'007

using namespace std;

int n;
int nCk[53][53];

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;
	for (int left = 0; left <= 52; ++left) {
		nCk[left][0] = 1;
		for (int right = 1; right < left; ++right) {
			nCk[left][right] = (nCk[left - 1][right - 1] + nCk[left - 1][right]) % DIV;
		}
		nCk[left][left] = 1;
	}

	//문제해결
	int ans = 0;
	for (int i = 1; i <= n / 4; ++i) {
		int extra = n - i * 4;
		// i는 뽑을 포카드 세트의 개수
		// extra 는 나머지 카드를 뽑을 개수

		// 포함배제 원리
		/*  각 세트가 몇번씩 더해지는지 보여주는 표
		*  i▼,세트▶	1		2		3		4		5		6
		*  1			1		2		3		4		5		6
		*  2			0		1		3		6		5C2		6C2
		*  3			0		0		1		4		5C3		6C3
		*  4			0		0		0		1		5C4		6C4
		*  
		*  위표를 참고해서 보면 결국 nCk[세트][1]~nCk[세트][세트] 의 횟수가 나온다.
		* 이것을 +, - 번갈아가면서 더해주면 nCk[세트][세트] == 1 가 남는다. 즉 한번만 더해지게 되는 것이다.
		*/
		if (i & 1) {	// i가 홀수일 경우 포함
			ans = (ans + nCk[13][i] * nCk[52 - i * 4][extra]) % DIV;
		}
		else {	// i가 짝수일 경우 배제
			ans = (ans - (nCk[13][i] * nCk[52 - i * 4][extra]) % DIV + DIV) % DIV;
		}
	}

	//출력
	cout << ans;
	
}


