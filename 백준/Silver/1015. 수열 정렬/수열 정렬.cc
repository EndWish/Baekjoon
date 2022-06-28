#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

using namespace std;

int n;


int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	vector<pair<int,int>> v;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		v.emplace_back(a, i);
	}

	//문제해결
	ranges::sort(v);

	vector<int> ans(v.size());
	for (int i = 0; i < n; ++i) {
		ans[v[i].second] = i;
	}
	
	//출력
	for (int i : ans)
		cout << i << " ";

}