#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

int n, m;
array<int, 200000> arr;

int q;


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}

	sort(arr.begin(), arr.begin() + n);

	for (int i = 0; i < m; ++i) {
		cin >> q;
		auto p = lower_bound(arr.begin(), arr.begin() + n, q);
		
		if (*p != q) {
			cout << -1;
		}
		else {
			cout << distance(arr.begin(), p);
		}

		cout << "\n";
	}

	//문제해결

	//출력

}