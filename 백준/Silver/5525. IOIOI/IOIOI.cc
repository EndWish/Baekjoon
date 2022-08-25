#include <iostream>
#include <vector>
#include <queue>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

int n, m;
string s;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m >> s;
	
	//문제해결
	int ans = 0;
	int count = 0;
	char prev = ' ';
	for (int i = 0; i < s.length(); ++i) {
		if (s[i] != prev)
			++count;
		else {
			if (s[i] == 'I')
				count = 1;
			else
				count = 0;
		}
		
		if (count >= n * 2 + 1 && (count & 1)) {
			++ans;
		}
		prev = s[i];
	}

	//출력
	cout << ans;
}