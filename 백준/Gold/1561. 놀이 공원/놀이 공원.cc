#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

 ll n, m;
 vector<int> arr;

 ll CountChildren(ll maxTime);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> m;

	arr.assign(m, 0);
	for (int& a : arr) {
		cin >> a;
	}

	if (n <= m) {
		cout << n;
		return 0;
	}

	//문제해결
	ll s = 0, e = n * 30LL;	//딱맞게 채울 수 있는 시간을 찾는다.
	while (s < e) {
		ll mid = (s + e) / 2;
		if (n <= CountChildren(mid)) {
			e = mid;
		}else{
			s = mid + 1;
		}
	}

	ll nChildren = CountChildren(s);
	//출력
	for (int i = m - 1; i >= 0; --i) {
		if (s % arr[i] == 0) {
			if (n < nChildren) {
				--nChildren;
			}
			else if (n == nChildren) {
				cout << i + 1;
				return 0;
			}
		}
	}

}

ll CountChildren(ll maxTime) {

	ll nChildren = m;	// 0분에는 모든 놀이기구가 비어있으므로, m부터 시작
	for (int a : arr) {
		nChildren += maxTime / a;
	}

	return nChildren;
}
