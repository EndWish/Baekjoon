#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

#define ll long long
#define pii pair<int,int> 
#define MAXN 100'001
#define INF numeric_limits<int>::max()

int n;
array<int, MAXN> height;
array<pii, MAXN * 4> segTree;

pii MakeSetTree(int index, int left, int right);
pii FindMinValue(int index, int left, int right, int start, int end);
int DFS(int start, int end);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> height[i];
	}

	//문제해결
	MakeSetTree(1, 1, n);

	//출력
	cout << DFS(1, n);

}

pii MakeSetTree(int index, int left, int right) {
	if (left == right) {	// 단말 노드일 경우
		return segTree[index] = { height[left], left };
	}

	int mid = (left + right) / 2;
	pii leftValue = MakeSetTree(index * 2, left, mid);
	pii rightValue = MakeSetTree(index * 2 + 1, mid + 1, right);
	return segTree[index] = min(leftValue, rightValue);
}

pii FindMinValue(int index, int left, int right, int start, int end) {
	// 범위 밖
	if (right < start || end < left)
		return { INF, -1 };

	//포함되는 경우
	if (start <= left && right <= end)
		return segTree[index];

	// 걸치는 경우
	int mid = (left + right) / 2;
	pii leftValue = FindMinValue(index * 2, left, mid, start, end);
	pii rightValue = FindMinValue(index * 2 + 1, mid + 1, right, start, end);
	return min(leftValue, rightValue);

}

int DFS(int start, int end) {
	if (end < 1 || n < start || end < start)
		return 0;

	if (start == end)
		return height[start];

	pii minValue = FindMinValue(1, 1, n, start, end);	// first = height, second = index
	int area = (end - start + 1) * minValue.first;

	return max({ area, DFS(start, minValue.second - 1), DFS(minValue.second + 1, end) });
}
