#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long
#define MAXN 100'001
#define MOD 1'000'000'007

int n, k;
vector<vector<ll>> dp;	// "dp[a][b] : 숫자b로 끝나는 길이가 a인 부분수열의 개수"를 리프노드로 하는 세그먼트 트리

void AddNum(vector<ll>& segTree, int index, int left, int right, ll pos, ll add);
ll GetSum(vector<ll>& segTree, int index, int left, int right, int start, int end);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> k;
	dp.assign(k + 1, vector<ll>(MAXN * 4, 0));

	//문제해결
	int num;
	for (int i = 0; i < n; ++i) {
		cin >> num;
		AddNum(dp[1], 1, 1, MAXN, num, 1);
		for (int len = 2; len <= k; ++len) {
			AddNum(dp[len], 1, 1, MAXN, num, GetSum(dp[len - 1], 1, 1, MAXN, 1, num - 1));
		}
	}

	cout << GetSum(dp[k], 1, 1, MAXN, 1, MAXN);

}

void AddNum(vector<ll>& segTree, int index, int left, int right, ll pos, ll add) {
	if (left == right) {
		segTree[index] += add;
		segTree[index] %= MOD;
		return;
	}

	int mid = (left + right) / 2;
	if (left <= pos && pos <= mid)
		AddNum(segTree, index * 2, left, mid, pos, add);
	else
		AddNum(segTree, index * 2 + 1, mid + 1, right, pos, add);

	segTree[index] = (segTree[index * 2] + segTree[index * 2 + 1]) % MOD;
}
ll GetSum(vector<ll>& segTree, int index, int left, int right, int start, int end) {
	if (right < start || end < left)
		return 0;
	if (start <= left && right <= end)
		return segTree[index];

	ll result = 0;
	int mid = (left + right) / 2;
	result += GetSum(segTree, index * 2, left, mid, start, end);
	result += GetSum(segTree, index * 2 + 1, mid + 1, right, start, end);
	result %= MOD;
	return result;
}
