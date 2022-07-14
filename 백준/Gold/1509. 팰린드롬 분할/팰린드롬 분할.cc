#include <iostream>
#include <string>
#include <algorithm>

#define MAXN 2500

using namespace std;

string str;
size_t strLen;
bool palindrome[MAXN][MAXN];	// a부터 b자리 까지의 문자는 팰린드롬인가?
int ans[MAXN];

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> str;
	strLen = str.length();
	for (int e = strLen; 0 <= e; --e) {
		for (int s = e; s < strLen; ++s) {
			palindrome[s][e] = true;	// 1자리 글자 또는 (s > e)인 경우 true로 초기화
		}
	}

	//문제해결
	for (int len = 2; len <= strLen; ++len) {
		for (int s = 0; s < strLen - len + 1; ++s) {
			int e = s + len - 1;
			if (palindrome[s + 1][e - 1] && str[s] == str[e])
				palindrome[s][e] = true;
		}
	}

	ans[0] = 1;
	for (int i = 1; i < strLen; ++i) {
		if (palindrome[0][i]) {	// 문자전체가 하나의 펠린드롬일 경우
			ans[i] = 1;
			continue;
		}

		ans[i] = i + 1;
		for (int k = 0; k < i; ++k) {	// k+1 ~ i번째 까지의 문자가 팰린드롬일때 0 ~ i번째 문자는 ans[k] + 1 개의 팰린드롬으로 분할가능
			if (palindrome[k + 1][i])
				ans[i] = min(ans[i], ans[k] + 1);
		}
	}

	//출력
	cout << ans[strLen - 1];

}