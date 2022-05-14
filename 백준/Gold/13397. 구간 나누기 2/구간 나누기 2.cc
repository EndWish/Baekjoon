#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<int> arr;

bool MakeSection(int maxScore);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> m;
	arr.assign(n, 0);
	for (int& a : arr)
		cin >> a;

	//문제해결
	int s = 0, e = 10'000 * 5'000;
	while (s < e) {
		int mid = (s + e) / 2;
		if (MakeSection(mid)) {
			e = mid;
		}
		else {
			s = mid + 1;
		}

	}
	
	//출력
	cout << s;

}

bool MakeSection(int maxScore) {
	int nSection = 1;
	int minimum = arr[0], maximum = arr[0];
	for (int a : arr) {
		minimum = min(minimum, a);
		maximum = max(maximum, a);

		if (maximum - minimum > maxScore) {
			++nSection;
			minimum = a;
			maximum = a;

			if (nSection > m)
				return false;

		}

	}

	return true;

}

