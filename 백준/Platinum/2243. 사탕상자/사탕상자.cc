#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>

#define MAXT 1'000'000
#define pii pair<int,int>

using namespace std;

int n;
vector<int> segTree;

void PushCandy(int index, int left, int right, int taste, int num);
int PopCandy(int index, int left, int right, int ranking);

int main() 
{

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	segTree.assign(MAXT * 4, 0);

	//문제해결
	int a, b, c;
	for (int i = 0; i < n; ++i) {
		cin >> a;
		if (a == 1) {
			cin >> b;
			cout << PopCandy(1, 1, MAXT, b) << "\n";
		}
		else {
			cin >> b >> c;
			PushCandy(1, 1, MAXT, b, c);
		}
	}

	//출력
	
}

void PushCandy(int index, int left, int right, int taste, int num) {
	if (left == right) {
		segTree[index] += num;
		return;
	}

	int mid = (left + right) / 2;
	if (left <= taste && taste <= mid) {
		PushCandy(index * 2, left, mid, taste, num);
	}
	else {
		PushCandy(index * 2 + 1, mid + 1, right, taste, num);
	}
	segTree[index] = segTree[index * 2] + segTree[index * 2 + 1];
}

int PopCandy(int index, int left, int right, int ranking) {
	int res;

	if (left == right) {
		segTree[index] -= 1;
		return left;
	}

	int mid = (left + right) / 2;
	if (ranking <= segTree[index * 2]) {
		res = PopCandy(index * 2, left, mid, ranking);
	}
	else {
		res = PopCandy(index * 2 + 1, mid + 1, right, ranking - segTree[index * 2]);
	}
	segTree[index] = segTree[index * 2] + segTree[index * 2 + 1];
	return res;
}
