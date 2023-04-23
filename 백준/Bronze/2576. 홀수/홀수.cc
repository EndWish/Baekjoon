#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int sum = 0;
	int minNum = 100;
	for (int i = 0; i < 7; ++i) {
		int num;
		cin >> num;
		if (num & 1) {
			sum += num;
			minNum = min(num, minNum);
		}
	}

	if (minNum == 100)
		cout << -1;
	else
		cout << sum << "\n" << minNum;
	
}


