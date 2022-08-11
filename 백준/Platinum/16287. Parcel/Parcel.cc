#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>

#define MAXW 200'001

using namespace std;

int w, n;
vector<int> a;
array<bool, MAXW * 2> pick2a;

int main() 
{

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> w >> n;
	a.assign(n, 0);
	for (int& value : a) {
		cin >> value;
	}

	//문제해결
	bool ans = false;
	for (int i = 2; i < n - 1; ++i) {
		for (int k = 0; k < i - 1; ++k) {
			pick2a[a[k] + a[i - 1]] = true;
		}

		for (int j = i + 1; j < n; ++j) {
			int late = w - a[i] - a[j];
			if (0 <= late && late < MAXW * 2 && pick2a[late]) {
				ans = true;
				break;
			}
		}

		if (ans) {
			break;
		}
	}

	//출력
	if (ans) {
		cout << "YES\n";
	}
	else {
		cout << "NO\n";
	}
	
}
