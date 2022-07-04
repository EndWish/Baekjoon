#include <iostream>
#include <vector>
#include <array>
#include <ranges>
#include <algorithm>

using namespace std;

int n, s;
long long ans;
vector<int> nums1, nums2, sums1, sums2;

void DFS(int index, int sum, const vector<int>& nums, vector<int>& sums);
void Print(vector<int>& vec);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n >> s;
	nums1.assign((n + 1) / 2, 0);
	nums2.assign(n - (n + 1) / 2, 0);
	for (int& v : nums1)
		cin >> v;
	for (int& v : nums2)
		cin >> v;

	if (n == 1) {
		cout << (nums1[0] == s ? 1 : 0);
		return 0;
	}

	//문제해결
	DFS(0, 0, nums1, sums1);	// num1 들로 가능한 조합들을 만들어 sums1에 저장
	//Print(sums1);
	DFS(0, 0, nums2, sums2);
	//Print(sums2);
	if (s == 0)	// s == 0일때 양쪽에서 아무것도 선택하지 안은 경우가 반드시 1개 존재
		--ans;

	ranges::sort(sums2);
	for (int v : sums1) {
		auto [b, e] = ranges::equal_range(sums2, s - v);
		ans += e - b;
	}

	//출력
	cout << ans;

}

void DFS(int index, int sum, const vector<int>& nums, vector<int>& sums)
{
	if (index == nums.size()) {
		sums.push_back(sum);
		return;
	}

	DFS(index + 1, sum, nums, sums);
	DFS(index + 1, sum + nums[index], nums, sums);
}

void Print(vector<int>& vec) 
{
	for (int v : vec)
		cout << v << " ";
	cout << "\n";
}
