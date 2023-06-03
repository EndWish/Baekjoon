#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

using namespace std;

#define ll long long

string str[2];
ll num[2];

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> str[0] >> str[1];
	for (int i = 0; i < 2; ++i) {
		for (char ch : str[i]) {
			num[i] += (ll)(ch - '0');
		}
	}

	cout << num[0] * num[1];
}


