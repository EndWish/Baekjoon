#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n;
vector<int> nums ,leftGCD, rightGCD;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	nums.assign(n, {});
	leftGCD.assign(n, {});
	rightGCD.assign(n, {});
	for (int i = 0; i < n; ++i) {
		cin >> nums[i];
		leftGCD[i] = nums[i];
		rightGCD[i] = nums[i];
	}

	for (int i = 1; i < n; ++i) {
		leftGCD[i] = gcd(leftGCD[i], leftGCD[i - 1]);
		rightGCD[n - 1 - i] = gcd(rightGCD[n - 1 - i], rightGCD[n - i]);
	}

	int totalGCD = rightGCD[0];

	int subNum = -1;
	int ans = -1;
	// 한 숫자씩 빼보자.
	for (int i = 0; i < n; ++i) {
		int newGCD = -1;
		if (i == 0) {
			newGCD = rightGCD[1];
		}
		else if (i == n - 1) {
			newGCD = leftGCD[n - 2];
		}
		else {
			newGCD = gcd(leftGCD[i - 1], rightGCD[i + 1]);
		}

		if (totalGCD < newGCD && nums[i] % newGCD != 0) {
			ans = newGCD;
			subNum = nums[i];
		}
	}

	if (ans == -1) {
		cout << ans;
	}
	else {
		cout << ans << " " << subNum;
	}

}

