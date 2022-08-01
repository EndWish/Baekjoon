#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>

#define ll long long

using namespace std;

int n, k;
vector<int> nums;
vector<int> ten;
vector<int> lens;
ll dp[1 << 15][100];	// dp[bit][r] : bit의 조합을 뽑았을때 나머지가 r인 경우의 개수

int StringMod(const string& s, int p);
ll Factorial(int num);
ll GCD(ll a, ll b);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	nums.assign(n, 0);
	lens.assign(n, 0);
	vector<string> input(n);

	// 1. string으로 입력받기
	for (string& s : input) {
		cin >> s;
	}
	cin >> k;
	
	// 2. 수를 k로 나눈 나머지와 수의 길이를 저장한다.
	for (int i = 0; i < n; ++i) {
		nums[i] = StringMod(input[i], k);
		lens[i] = input[i].length();
	}

	// 3. 10의 i승 을 k 로 나눈 나머지들을 저장한다.
	ten.assign(51, 0);
	ten[0] = 1 % k;
	for (int i = 1; i <= 50; ++i) {
		ten[i] = (ten[i - 1] * 10) % k;
	}

	//문제해결
	dp[0][0] = 1;
	for (int bit = 0; bit < (1 << n); ++bit) {	// 조합의 수만큼, 0부터 순서대로 해도 되는 이유는 만약 bit가 101이라고 했을때 무조건 100 과 001을 거쳐오기 때문에 값이 전부 누적이 된다.
		for (int pick = 0; pick < n; ++pick) {	// pick번째 수를 추가했을때
			if (((1 << pick) & bit) == 0) {	// 아직 조합에 없는 숫자를 추가할 경우
				int nextBit = bit | (1 << pick);
				for (int r = 0; r < k; ++r) {	// 가능한 나머지의 수만큼
					int nextR = ((r * ten[lens[pick]]) % k + nums[pick]) % k;
					// [참고] 123와 456을 붙인다고 생각 하면 (123 * 1000 + 456) % k == ((123 % k) * (1000 % k) + (456 % k)) % k 로 바꿀수 있다.
					// 123 % k, 1000 % k, 456 % k 은 각각 r, ten[lens], nums[pick] 에 해당한다. 
					dp[nextBit][nextR] += dp[bit][r];
				}
			}
		}
	}

	//출력
	ll p = dp[(1 << n) - 1][0];
	ll q = Factorial(n);
	ll gcd = GCD(p, q);
	cout << (p / gcd) << "/" << q / gcd;
	
}

int StringMod(const string& s, int p) {
	int res = 0;
	for (int i = 0; i < s.length(); ++i) {
		res = (res * 10 + (s[i] - '0')) % p;
	}
	return res;
}

ll Factorial(int num) {
	ll res = 1;
	ll i = 1;
	while (i <= num) {
		res *= i++;
	}
	return res;
}

ll GCD(ll a, ll b) {
	if (a < b) {	// a가 b보가 커야한다.
		swap(a, b);
	}

	if (b == 0)
		return a;
	return GCD(b, a % b);
}
