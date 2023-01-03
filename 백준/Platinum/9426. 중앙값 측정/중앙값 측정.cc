#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <ranges>

using namespace std;

#define ll long long

int n, k;
vector<ll> nums;
multiset<ll, greater<ll>> front;
multiset<ll> back;

void Push(ll x);
void Balancing();
void Pop(ll x);
void Print();

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n >> k;
	nums.assign(n, {});
	for (ll& num : nums) {
		cin >> num;
	}

	//문제해결
	ll ans = 0;
	for (int i = 0; i < k - 1; ++i) {
		Push(nums[i]);
	}
	for (int i = k - 1; i < n; ++i) {
		Push(nums[i]);
		ans += *front.begin();
		//Print();
		Pop(nums[i - (k - 1)]);
	}

	//출력
	cout << ans;

}

void Push(ll x) {

	// 예외처리 : front나 back이 비어있을경우 
	if (front.empty()) {
		front.insert(x);
		return;
	}
	if (back.empty()) {
		ll ftop = *front.begin();
		if (x < ftop) {
			front.erase(ftop);
			front.insert(x);
			back.insert(ftop);
		}
		else {
			back.insert(x);
		}
		return;
	}

	ll ftop = *front.begin();
	if (x <= ftop) {
		front.insert(x);
	}
	else {
		back.insert(x);
	}

	Balancing();
}

void Balancing() {
	while (front.size() > back.size() + 1) {
		ll ftop = *front.begin();
		front.erase(front.begin());
		back.insert(ftop);
	}
	while (front.size() < back.size()) {
		ll btop = *back.begin();
		back.erase(back.begin());
		front.insert(btop);
	}
}

void Pop(ll x) {
	if (front.contains(x)) {
		//front.erase(x);	// 모든 x를 삭제 해버리기 때문에 사용x
		auto it = front.find(x);
		front.erase(it);
	}
	else {
		//back.erase(x);	// 모든 x를 삭제 해버리기 때문에 사용x
		auto it = back.find(x);
		back.erase(it);
	}

	Balancing();
}

void Print() {
	cout << "front : ";
	for (ll num : front)
		cout << num << " ";

	cout << "back : ";
	for (ll num : back)
		cout << num << " ";

	cout << "\n";
}