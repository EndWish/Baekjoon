#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXN 1001
#define INF numeric_limits<int>::max()
#define pci pair<char,int>

using namespace std;

string str, explosion;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> str >> explosion;
	stack<pci> s;

	//문제해결
	int j = 0;
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == explosion[j]) {
			s.emplace(str[i], j);
			++j;
		}
		else {
			j = 0;
			if (str[i] == explosion[j]) {
				s.emplace(str[i], 0);
				++j;
			}
			else
				s.emplace(str[i], -1);
		}

		if (j == explosion.size()) {
			for (int k = 0; k < explosion.size(); ++k)
				s.pop();

			if (s.empty())
				j = 0;
			else
				j = s.top().second + 1;
		}

	}

	//출력
	string ans(s.size(), {});
	for (int i = ans.size() - 1; i >= 0; --i) {
		ans[i] = s.top().first;
		s.pop();
	}

	if (ans.empty())
		cout << "FRULA";
	else
		cout << ans;

}

