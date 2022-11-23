#include <iostream>
#include <array>
#include <vector>
//#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>

using namespace std;

int n, m;
vector<int> cranes, boxes;
int ans;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;
	cranes.assign(n, {});
	for (int& crane : cranes)
		cin >> crane;
	cin >> m;
	boxes.assign(m, {});
	for (int& box : boxes)
		cin >> box;

	//문제해결
	sort(cranes.begin(), cranes.end(), greater<int>{});
	sort(boxes.begin(), boxes.end(), greater<int>{});
	cranes.push_back(0);

	if (cranes[0] < boxes[0]) {
		cout << -1;
		return 0;
	}

	for (int i = 1; i <= n; ++i) {
		
		int boxNum = distance(boxes.begin(), lower_bound(boxes.begin(), boxes.end(), cranes[i], greater<int>{}));
		ans = max(ans, (boxNum + i - 1) / i);
		//cout << cranes[i - 1] << " 크레인 까지 사용 : 박스 - " << boxNum << ", " << (boxNum + i - 1) / i << "분\n";
	}

	//출력
	cout << ans;

}