#include <iostream>
#include <array>
#include <algorithm>

//14863
#define MAXK 100'000

using namespace std;

int n, k;
array<int, MAXK + 1> dp;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> k;

	//문제해결
	pair<int, int> input[2];

	int minTime = 0;
	for (int i = 0; i < n; ++i) {
		cin >> input[0].first >> input[0].second;
		cin >> input[1].first >> input[1].second;
		
		
		for (int j = k; j >= minTime; --j) {
			int path0 = minTime <= j - input[0].first ? dp[j - input[0].first] + input[0].second : 0;
			int path1 = minTime <= j - input[1].first ? dp[j - input[1].first] + input[1].second : 0;
			dp[j] = max(path0, path1);
		}
		minTime += min(input[0].first, input[1].first);
	}
	
	//출력
	cout << dp[k];

}