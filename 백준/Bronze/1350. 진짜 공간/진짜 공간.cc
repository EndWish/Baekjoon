#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

using namespace std;

#define ll long long

int n;
vector<ll> nums;
ll cluster;

ll getUseClusterNum(ll fileSize);

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n;
	nums.assign(n, {});
	for (ll& num : nums)
		cin >> num;
	cin >> cluster;

	ll numOfUseCluster = 0;
	for (ll num : nums) {
		numOfUseCluster += getUseClusterNum(num);
	}

	cout << numOfUseCluster * cluster;

	
}

ll getUseClusterNum(ll fileSize) {
	return (fileSize + cluster - 1) / cluster;
}
