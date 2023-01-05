#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n, h;
vector<int> unders, overs;

int Crash(int line);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> h;
	int under, over;
	for (int i = 0; i < n / 2 ; ++i) {
		cin >> under >> over;
		unders.push_back(under);
		overs.push_back(over);
	}

	//문제해결
	ranges::sort(unders);
	ranges::sort(overs);
	int minCrash = numeric_limits<int>::max();
	int numOfLine = 0;
	for (int i = 1; i <= h; ++i) {
		int crash = Crash(i);
		if (crash < minCrash) {
			minCrash = crash;
			numOfLine = 1;
		}
		else if (crash == minCrash) {
			++numOfLine;
		}
	}

	//출력
	cout << minCrash << " " << numOfLine;

}

int Crash(int line) {
	int result = 0;
	result += ranges::distance(ranges::lower_bound(unders, line), unders.end());
	result += ranges::distance(ranges::upper_bound(overs, h - line), overs.end());
	return result;
}
