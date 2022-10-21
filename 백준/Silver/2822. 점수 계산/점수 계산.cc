#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define pii pair<int,int>

array<pii, 8> scores;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	for (int i = 0; i <= 7; ++i) {
		cin >> scores[i].first;
		scores[i].second = i + 1;
	}

	//문제해결
	ranges::sort(scores, greater<int>{}, &pii::first);
	int sum = 0;
	vector<int> numbers;
	for (int i = 0; i < 5; ++i) {
		sum += scores[i].first;
		numbers.push_back(scores[i].second);
	}
	ranges::sort(numbers);

	//출력
	cout << sum << "\n";
	for (int number : numbers)
		cout << number << " ";

}