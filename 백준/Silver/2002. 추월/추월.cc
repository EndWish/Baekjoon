#include <iostream>
#include <array>
#include <string>
#include <unordered_map>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define MAXN 1001

int n;
unordered_map<string, int> matching;
vector<int> nums;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	string input;

	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> input;
		matching[input] = i;
	}
	for (int i = 0; i < n; ++i) {
		cin >> input;
		nums.push_back(matching[input]);
	}
	
	//문제해결
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (nums[i] > nums[j]) {
				++ans;
				break;
			}
		}
	}

	//출력
	cout << ans;

}