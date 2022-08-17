#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

#define MAXN 100'001
#define MAXNM 200'001

using namespace std;

int t;
int n, m;
vector<int> segTree;
vector<int> pos;
int nextPos;

void MakeSegTree(int index, int left, int right);
int Query(int index, int left, int right, int start, int end);
void Change(int index, int left, int right, int p, int add);

int main() 
{

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	segTree.assign(MAXNM * 4, 0);
	pos.assign(MAXN, 0);

	cin >> t;
	while (t-- > 0) {
		//초기화,입력값 받기
		ranges::fill(segTree, 0);
		ranges::fill(pos, 0);

		cin >> n >> m;
		for (int i = 1; i <= n; ++i) {
			pos[i] = n + 1 - i;
		}

		MakeSegTree(1, 1, MAXNM - 1);
		nextPos = n + 1;
		//문제해결
		int num;
		for (int i = 0; i < m; ++i) {
			cin >> num;
			cout << Query(1, 1, MAXNM - 1, pos[num] + 1, MAXNM - 1) << " ";
			Change(1, 1, MAXNM - 1, pos[num], -1);
			pos[num] = ++nextPos;
			Change(1, 1, MAXNM - 1, pos[num], 1);
		}
		cout << "\n";

		//출력
	}


}

void MakeSegTree(int index, int left, int right) {
	if (left == right) {
		if (left <= n) {
			segTree[index] = 1;
			//cout << format("{}~{}의 합 : {}\n", left, right, segTree[index]);
		}
		return;
	}

	if (n < left) {
		return;
	}

	int mid = (left + right) / 2;
	MakeSegTree(index * 2, left, mid);
	MakeSegTree(index * 2 + 1, mid + 1, right);
	segTree[index] = segTree[index * 2] + segTree[index * 2 + 1];
	//cout << format("{}~{}의 합 : {}\n", left, right, segTree[index]);

}

int Query(int index, int left, int right, int start, int end) {
	if (start <= left && right <= end) {
		return segTree[index];
	}
	if (right < start || end < left) {
		return 0;
	}
	int mid = (left + right) / 2;
	return Query(index * 2, left, mid, start, end) + Query(index * 2 + 1, mid + 1, right, start, end);

}

void Change(int index, int left, int right, int p, int add) {
	if (left == right) {	// == p
		segTree[index] += add;
		return;
	}

	int mid = (left + right) / 2;
	if (left <= p && p <= mid) {
		Change(index * 2, left, mid, p, add);
	}
	else {
		Change(index * 2 + 1, mid + 1, right, p, add);
	}
	segTree[index] = segTree[index * 2] + segTree[index * 2 + 1];
}