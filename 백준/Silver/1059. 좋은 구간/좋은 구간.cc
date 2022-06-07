#include <iostream>
#include <vector>
#include <ranges>
#include <numeric>
#include <algorithm>

#define MAXN 50

using namespace std;

int l;
vector<int> v;
int n;


int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> l;
	v.assign(l, 0);
	for (int& i : v)
		cin >> i;
	cin >> n;

	//문제해결
	int s = 0;
	int e = numeric_limits<int>::max();
	for (int i : v) {
		if (i <= n)
			s = max(s, i);
		if (n <= i)
			e = min(e, i);
	}

	int ans = 0;
	if (s != e) {
		ans = (n - s) * (e - n) - 1;
	}

	//출력
	cout << ans;

}