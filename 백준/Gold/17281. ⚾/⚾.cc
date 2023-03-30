#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define M 9

int n;
vector<array<int, 10>> results;	// result[이닝][선수] = 결과
array<int, 10> batter;

int Play();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;

	results.assign(n + 1, {});
	for (int inning = 1; inning <= n; ++inning) {
		for (int player = 1; player <= 9; ++player) {
			cin >> results[inning][player];
		}
	}

	int ans = 0;
	iota(batter.begin(), batter.end(), 0);
	do {
		// 4번 타자가 1번 선수가 아닐경우 다음 사이클로 이동
		if (batter[4] != 1)
			continue;

		// 게임을 진행한다.
		ans = max(ans, Play());

	} while (ranges::next_permutation(batter.begin() + 1, batter.end()).found);

	cout << ans;

}

int Play() {
	// 초기화
	int score = 0;
	int batterNum = 1;
	// N번의 이닝을 진행한다.
	for (int inning = 1; inning <= n; ++inning) {
		int out = 0;
		int runner = 0;

		while (out < 3) {
			int result = results[inning][batter[batterNum]];	// 공격결과를 얻어온다.

			// 공격 결과를 반영한다.
			runner |= (1 << 0);
			for (int i = 0; i < result; ++i) {
				runner <<= 1;
				if (runner & (1 << 4))
					++score;
			}

			// out을 확인하고 추가한다.
			if (result == 0)
				++out;

			// 타자를 바꾼다.
			batterNum = (batterNum % 9) + 1;
		}
	}

	return score;
}
