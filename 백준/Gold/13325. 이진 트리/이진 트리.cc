#include <iostream>
#include <array>
#include <numeric>
#include <cmath>
#include <execution>

using namespace std;

#define ll long long

int k;
ll maxn;
array<ll, 2'100'000> edges;
array<ll, 2'100'000> dp;

void SetDP(int node);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> k;
	maxn = pow(2, k + 1) - 1;
	for (ll i = 2; i <= maxn; ++i) {
		cin >> edges[i];
	}
	
	//문제해결
	SetDP(1);

	//출력
	ll sum = reduce(execution::par, edges.begin() + 2, edges.begin() + maxn + 1);
	cout << sum;
}

void SetDP(int node) {
	if (node * 2 > maxn) {	// 리프 노드일 경우
		dp[node] = edges[node];
		return;
	}

	int left = node * 2;
	int right = node * 2 + 1;
	SetDP(left);
	SetDP(right);

	if (dp[left] != dp[right]) {	// 거리가 더 짧은 노드의 길이를 늘린다.
		int addNode = dp[left] < dp[right] ? left : right;
		int diff = abs(dp[left] - dp[right]);
		dp[addNode] += diff;
		edges[addNode] += diff;
	}

	dp[node] = dp[left] + edges[node];
}
