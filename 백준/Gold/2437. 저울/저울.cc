#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <tuple>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define MAXN 15
#define INF numeric_limits<int>::max()
#define pii pair<int,int>

int n;
vector<int> weight;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	weight.assign(n, 0);
	for (int& w : weight)
		cin >> w;
	
	//문제해결
	ranges::sort(weight);
	int wIndex = 0;
	for (int i = 1; i <= 1'000'000'001; ) {
		if (weight[wIndex] <= i) {	// 가능한 경우
			i = i + weight[wIndex];
			if (++wIndex == weight.size()) {
				cout << i;
				break;
			}
		}
		else {	// 불가능한 경우
			cout << i;
			break;
		}
	}

	//출력

}
