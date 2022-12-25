#include <iostream>
#include <vector>

using namespace std;

int n, v;
vector<int> vec;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	vec.assign(n, {});
	for (int& val : vec)
		cin >> val;
	cin >> v;
	
	//문제해결
	int ans = 0;
	for (int i = 0; i < n; ++i)
		if (vec[i] == v)
			++ans;

	//출력
	cout << ans;

}