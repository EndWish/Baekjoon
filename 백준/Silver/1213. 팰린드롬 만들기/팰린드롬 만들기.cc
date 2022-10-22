#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

string input;
array<char, 26> num;

queue<char> head;
stack<char> tail;
char mid;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> input;
	for (char ch : input)
		++num[ch - 'A'];

	//문제해결
	for (int i = 0; i < 26; ++i) {
		for (int j = 0; j < num[i] / 2; ++j) {
			head.push(i + 'A');
			tail.push(i + 'A');
		}
		if (num[i] & 1) {	// 홀수일 경우
			if (mid == 0) {
				mid = i + 'A';
			}
			else {
				cout << "I'm Sorry Hansoo";
				return 0;
			}
		}
	}

	//출력
	while (!head.empty()) {
		cout << head.front();
		head.pop();
	}
	if (mid != 0)
		cout << mid;
	while (!tail.empty()) {
		cout << tail.top();
		tail.pop();
	}

}