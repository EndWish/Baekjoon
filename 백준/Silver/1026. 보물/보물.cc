#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n;



int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;
	vector<int> v1(n);
	vector<int> v2(n);
	for (int& i : v1)
		cin >> i;
	for (int& i : v2)
		cin >> i;

	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end(), greater<int>());

	//문제해결
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		ans += v1[i] * v2[i];
	}

	//출력
	cout << ans;

}