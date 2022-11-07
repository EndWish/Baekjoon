#include <iostream>
#include <deque>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

int n;
deque<pair<int,int>> balloons;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	//초기화,입력값 받기
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int input;
		cin >> input;
		balloons.emplace_back(i, input);
	}

	//문제해결
	while (true) {
		// 풍선 제거
		auto [number, move] = balloons.front();
		cout << number << " ";
		balloons.pop_front();
		if (balloons.empty())
			break;

		if (0 < move)
			--move;
		move %= (int)balloons.size();

		while (0 < move) {
			balloons.push_back(balloons.front());
			balloons.pop_front();
			--move;
		}
		while (move < 0) {
			balloons.push_front(balloons.back());
			balloons.pop_back();
			++move;
		}

	}

	//출력

}