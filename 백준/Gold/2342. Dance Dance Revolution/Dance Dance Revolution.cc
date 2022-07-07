#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <ranges>
#include <cmath>
#include <numeric>

#define MAXN 100'001

using namespace std;

int n;
array<int, MAXN> cmd;
vector<int> dp[5][5];

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기

	// 1. 입력값 받기
	for (int i = 1; i < MAXN; ++i) {
		cin >> cmd[i];
		++n;
		if (cmd[i] == 0) {
			--n;
			break;
		}
	}

	// 2. dp초기화 하기
	for (int i = 0; i < 5; ++i)
		for (int j = i; j < 5; ++j)
			dp[i][j].assign(MAXN, -1);	// vector 할당

	dp[0][0][0] = 0;	// 처음에는 두발다 0에 있다.

	//문제해결
	for (int i = 1; i <= n; ++i) {
		
		int step1 = cmd[i];	// 옮기는 발
		for (int step2 = 0; step2 < 5; ++step2) {	// 고정된 다른 발
			if (step1 == step2)
				continue;

			for (int preStep = 0; preStep < 5; ++preStep) {	// 옮기기전 위치

				int curSteps[2] = { step1, step2 };
				ranges::sort(curSteps);
				int& curDP = dp[curSteps[0]][curSteps[1]][i];

				int preSteps[2] = { preStep, step2 };
				ranges::sort(preSteps);
				int preDP = dp[preSteps[0]][preSteps[1]][i - 1];

				if (preDP == -1)
					continue;

				// 같은 위치 : 1
				if (step1 == preStep) {
					curDP = (curDP == -1) ? preDP + 1 : min(curDP, preDP + 1);
				}
				// 중앙에서 이동할 경우
				else if (preStep == 0) {
					curDP = (curDP == -1) ? preDP + 2 : min(curDP, preDP + 2);
				}
				// 대각선 이동
				else if (abs(step1 - preStep) != 2) {
					curDP = (curDP == -1) ? preDP + 3 : min(curDP, preDP + 3);
				}
				// 반대편 이동
				else {
					curDP = (curDP == -1) ? preDP + 4 : min(curDP, preDP + 4);
				}

			}

		}


	}

	//출력
	int ans = numeric_limits<int>::max();
	for (int i = 0; i < 5; ++i) {
		for (int j = i; j < 5; ++j) {
			if (dp[i][j][n] != -1)
				ans = min(ans, dp[i][j][n]);
		}
	}
	cout << ans;

}