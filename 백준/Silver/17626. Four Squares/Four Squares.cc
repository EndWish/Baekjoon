#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n;

int Solved();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;

	//문제해결
	cout << Solved();

}

int Solved() {
	unordered_set<int> s1;
	for (int i = 1; i <= n; ++i) {
		int num = i * i;
		if (num <= n)
			s1.insert(num);
	}

	// 1. 1개로 표현이 가능한 경우
	if (s1.contains(n))
		return 1;

	// 2. 2개로 표현이 가능한 경우
	unordered_set<int> s2;
	for (int num1 : s1) {
		for (int num2 : s1) {
			int num = num1 + num2;
			if (num <= n)
				s2.insert(num);
		}
	}
	if (s2.contains(n))
		return 2;

	// 3. 3개로 표현이 가능한 경우
	for (int num1 : s1) {
		if (s2.contains(n - num1))
			return 3;
	}

	return 4;
}