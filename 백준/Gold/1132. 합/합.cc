#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long

int n;
string s;
array<ll, 10> digit;
int zeroImpossible = 0;
array<ll, 10> nums;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	nums.fill(-1);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> s;
		ll mul = 1;
		for (char ch : s | views::reverse) {
			digit[ch - 'A'] += mul;
			mul *= 10;
		}
		zeroImpossible |= 1 << (s[0] - 'A');
	}

	for (ll i = 0; i < 10; ++i) {
		// 가장 digit이 적은 수의 인덱스를 찾는다.
		int index = -1;
		ll minDigit = numeric_limits<ll>::max();
		for (int j = 0; j < 10; ++j) {
			if (nums[j] == -1 && digit[j] < minDigit) {
				if (i == 0 && (zeroImpossible & (1 << j)) != 0)
					continue;
				index = j;
				minDigit = digit[j];
			}
		}

		nums[index] = i;
	}

	// 합을 구한다.
	ll sum = inner_product(digit.begin(), digit.end(), nums.begin(), 0LL);
	cout << sum;

}

