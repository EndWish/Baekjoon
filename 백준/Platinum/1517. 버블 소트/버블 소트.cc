#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long

int n;
vector<ll> nums;

ll MergeSort(int start, int end);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	nums.assign(n, {});
	for (ll & num : nums)
		cin >> num;

	//문제해결
	cout << MergeSort(0, nums.size() - 1);

	//출력

}

ll MergeSort(int start, int end) {
	if (start == end)
		return 0;
	
	ll result = 0;

	int mid = (start + end) / 2;
	result += MergeSort(start, mid);
	result += MergeSort(mid + 1, end);

	//cout << start << "-" << end << "정렬\n";
	vector<ll> left(nums.begin() + start, nums.begin() + mid + 1);
	vector<ll> right(nums.begin() + mid + 1, nums.begin() + end + 1);

	int input = start;
	int leftIndex = 0, rightIndex = 0;
	while (leftIndex < left.size() && rightIndex < right.size()) {
		if (left[leftIndex] > right[rightIndex]) {
			//cout << left[leftIndex] << "와 " << right[rightIndex] << "를 바꾼다:";
			nums[input++] = right[rightIndex++];
			result += left.size() - leftIndex;
			//cout << " +" << mid - leftIndex + 1 << "\n";
		}
		else {
			nums[input++] = left[leftIndex++];
		}
	}

	if (leftIndex == mid + 1) {	// 왼쪽이 먼저 비었을 경우
		while (rightIndex < right.size()) {
			nums[input++] = right[rightIndex++];
		}
	}
	else {	// 오른쪽이 먼저 비었을 경우
		while (leftIndex < left.size()) {
			nums[input++] = left[leftIndex++];
		}
	}

	return result;
}
