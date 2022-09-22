#include <iostream>
#include <vector>
#include <stack>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

int n, k;
stack<char> s1, s2;

void GoAscending();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> k;
	char input;
	for (int i = 0; i < n; ++i) {
		cin >> input;
		s1.push(input);
	}
	while (!s1.empty()) {
		s2.push(s1.top());
		s1.pop();
	}

	//문제해결
	GoAscending();
	for (int i = 0; i < k; ++i) {
		s1.pop();	// 숫자 삭제
		GoAscending();
	}

	//출력
	while (!s1.empty()) {
		s2.push(s1.top());
		s1.pop();
	}
	while (!s2.empty()) {
		cout << s2.top();
		s2.pop();
	}

}

void GoAscending() {
	while (!s2.empty() && (s1.empty() || s1.top() >= s2.top())) {
		s1.push(s2.top());
		s2.pop();
	}
}
