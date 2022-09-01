#include <iostream>
#include <vector>
#include <stack>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>



using namespace std;

int n, k;
vector<int> score;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> k;
	score.assign(n, {});
	for (int& v : score)
		cin >> v;

	//문제해결
	ranges::sort(score, greater<int>());

	//출력
	cout << score[k - 1];

}