#include <iostream>
#include <string>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

#define MAXN 10'001

// 효율적인 해킹

int n;
string s;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> s;

		//문제해결
		ranges::sort(s);

		//출력
		do {
			cout << s << "\n";
		} while (ranges::next_permutation(s).found);

	}
	


}
