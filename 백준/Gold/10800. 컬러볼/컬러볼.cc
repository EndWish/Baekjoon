#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;
#define ll long long
#define tlll tuple<ll,ll,ll>

int n;
vector<tlll> balls;	// size, color, number

ll dpSum;
array<ll, 200'001> dp;
array<ll, 200'001> ans;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	
	//초기화,입력값 받기
	cin >> n;
	balls.assign(n, {});
	for (int i = 0; auto & [size, color, number] : balls) {
		cin >> color >> size;
		number = i + 1;
		++i;
	}
		

	//문제해결
	ranges::sort(balls);
	int j = 0;
	int currentSize = get<0>(balls[0]);
	for (int i = 0; i < balls.size(); ++i) {
		auto [size, color, number] = balls[i];

		// 자신보다 작은 공들을 추가한다.
		if (currentSize < size) {	
			while (j < i) {
				dpSum += get<0>(balls[j]);
				dp[get<1>(balls[j])] += get<0>(balls[j]);
				++j;
			}
			currentSize = size;
		}

		ans[number] = dpSum - dp[color];
	}

	//출력
	for (int i = 1; i <= n; ++i) {
		cout << ans[i] << "\n";
	}

}