#include <iostream>
#include <vector>
#include <string>
#include <span>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

int n, m;
vector<string> a, b;
vector<string> ans;

int main() 
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> m;
	string str;
	for (int i = 0; i < n; ++i) {
		cin >> str;
		a.push_back(str);
	}

	//문제해결
	ranges::sort(a);
	for (int i = 0; i < m; ++i) {
		cin >> str;
		if (ranges::binary_search(a, str)) {
			ans.push_back(str);
		}
	}

	ranges::sort(ans);

	//출력
	cout << ans.size() << "\n";
	for (const string& s : ans) {
		cout << s << "\n";
	}

}