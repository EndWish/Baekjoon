#include <iostream>
#include <vector>
#include <ranges>

#define MOD 1'000'000'007
#define ll long long

using namespace std;

int n, m, k;
vector<ll> nums;
vector<ll> segTree;

void MakeSegTree(int index, int left, int right);
void ChangeNum(int index, int left, int right, int pos, ll num);
ll GetMul(int index, int left, int right, int start, int end);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> m >> k;
	nums.assign(n + 1, 0);
	segTree.assign(n * 4, 0);

	for (ll& val : nums | views::drop(1))
		cin >> val;

	//문제해결
	MakeSegTree(1, 1, n);
	ll a, b, c;
	for (int i = 0; i < m + k; ++i) {
		cin >> a >> b >> c;
		if (a == 1) {	// b번째 수를 c로 바꾸기
			ChangeNum(1, 1, n, b, c);
		}
		else {	// b부터 c까지의 곱을 출력
			cout << GetMul(1, 1, n, b, c) << "\n";
		}
	}

	//출력
	
}

void MakeSegTree(int index, int left, int right) 
{
	if (left == right) {
		segTree[index] = nums[left];
		return;
	}

	int mid = (left + right) / 2;
	MakeSegTree(index * 2, left, mid);
	MakeSegTree(index * 2 + 1, mid + 1, right);
	segTree[index] = (segTree[index * 2] * segTree[index * 2 + 1]) % MOD;

}

void ChangeNum(int index, int left, int right, int pos, ll num) 
{
	if (left == right) {	// left == right == pos
		segTree[index] = num;
		return;
	}

	int mid = (left + right) / 2;
	if (left <= pos && pos <= mid) {	//pos의 위치가 왼쪽일 경우
		ChangeNum(index * 2, left, mid, pos, num);
	}
	else {	//pos의 위치가 오른쪽일 경우
		ChangeNum(index * 2 + 1, mid + 1, right, pos, num);
	}
	segTree[index] = (segTree[index * 2] * segTree[index * 2 + 1]) % MOD;

}

ll GetMul(int index, int left, int right, int start, int end) 
{
	if (start <= left && right <= end) {
		return segTree[index];
	}
	if (right < start || end < left) {
		return 1LL;
	}

	int mid = (left + right) / 2;
	ll leftNum = GetMul(index * 2, left, mid, start, end);
	ll rightNum = GetMul(index * 2 + 1, mid + 1, right, start, end);
	return (leftNum * rightNum) % MOD;

}
