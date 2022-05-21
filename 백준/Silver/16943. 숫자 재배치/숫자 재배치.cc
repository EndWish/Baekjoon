#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int a, b, c;
vector<int> v;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> a >> b;
	while (a > 0) {
		v.push_back(a % 10);
		a /= 10;
	}

	//문제해결
	int max = -1;

	sort(v.begin(), v.end());
	do {
		if (*v.begin() == 0)
			continue;

		int num = 0;
		for (int n : v) {
			num *= 10;
			num += n;
		}

		if (num < b) {
			max = std::max(max, num);
		}

	} while (next_permutation(v.begin(), v.end()));
	
	//출력
	cout << max;

}