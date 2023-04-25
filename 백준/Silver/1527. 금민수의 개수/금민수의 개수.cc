#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long

ll a, b;
ll ans;

int getLeng(ll num);
bool goldMinSu(ll num, int leng);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	
	cin >> a >> b;

	int leng = 1;
	while (true) {
		if(!goldMinSu(0, leng++))
			break;
	}
	cout << ans;

}

bool goldMinSu(ll num, int leng) {
	if (getLeng(num) == leng) {
		if (b < num)
			return false;
		if (a <= num)
			++ans;
		return true;
	}

	if (!goldMinSu(num * 10LL + 4, leng))
		return false;

	if (!goldMinSu(num * 10LL + 7, leng))
		return false;

	return true;
}

int getLeng(ll num) {
	int result = 0;
	while (0 < num) {
		num /= 10;
		++result;
	}
	return result;
}
