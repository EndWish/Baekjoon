#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <tuple>
#include <ranges>
#include <algorithm>
#include <numeric>

#define ll long long

using namespace std;

int n;
vector<int> B;
array<int, 1'000'001> AIndex;

vector<int> segTree;

int Query(int index, int left, int right, int start, int end);
void Connect(int index, int left, int right, int pos);

int main() 
{

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	B.assign(n + 1, 0);
	segTree.assign(n * 4 + 1, 0);

	int num;
	for (int i = 1; i <= n; ++i) {
		cin >> num;
		AIndex[num] = i;
	}
	for (int i = 1; i <= n; ++i) {
		cin >> num;
		B[i] = AIndex[num];
	}

	//문제해결
	ll ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans += Query(1, 1, n, B[i], n);
		Connect(1, 1, n, B[i]);
	}

	//출력
	cout << ans;
	
}

int Query(int index, int left, int right, int start, int end) {
	if (end < left || right < start)
		return 0;
	if (start <= left && right <= end)
		return segTree[index];

	int mid = (left + right) / 2;
	return Query(index * 2, left, mid, start, end) + Query(index * 2 + 1, mid + 1, right, start, end);
}

void Connect(int index, int left, int right, int pos) {
	if (left == right) {	// (== pos)
		segTree[index] = 1;
		return;
	}

	int mid = (left + right) / 2;
	if (left <= pos && pos <= mid) {
		Connect(index * 2, left, mid, pos);
	}
	else {
		Connect(index * 2 + 1, mid + 1, right, pos);
	}
	segTree[index] = segTree[index * 2] + segTree[index * 2 + 1];
}