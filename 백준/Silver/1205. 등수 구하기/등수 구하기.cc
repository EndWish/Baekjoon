#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

using namespace std;

#define ll long long

int n, tesu, p;
vector<ll> scores;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> tesu >> p;
	scores.assign(n, {});
	for (ll& score : scores)
		cin >> score;
	
	//문제해결
	auto point = ranges::lower_bound(scores, tesu, greater<ll>());
	int rank = ranges::distance(scores.begin(), point) + 1;

	//출력

	if (scores.size() == p && tesu <= scores[p - 1]) {
		cout << -1;
	}
	else {
		cout << rank;
	}

}