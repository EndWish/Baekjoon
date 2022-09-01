#include <iostream>
#include <vector>
#include <stack>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define ll long long

using namespace std;

ll a, b;
vector<ll> arr1, arr2;

void GetOneNum(ll num, vector<ll>& arr);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> a >> b;

	//문제해결
	
	GetOneNum(a -1, arr1);
	GetOneNum(b, arr2);
	
	for (int i = 0; i < arr1.size(); ++i) {
		arr2[i] -= arr1[i];
	}

	//출력
	ll ans = 0;
	for (int i = arr2.size() - 1; i >= 0; --i) {
		ans *= 2;
		if(arr2[i] & 1)
			ans += 1;
	}
	cout << ans;

}

void GetOneNum(ll num, vector<ll>& arr) {

	ll mul = 1;
	while (true) {
		ll count = 0;
		count += (num + 1) / (mul * 2) * mul;
		count += max((num + 1) % (mul * 2) - mul, 0LL);
		arr.push_back(count);

		mul *= 2;
		if (num < mul)
			break;
	}
}
