#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int n, k;
int multitapCount = 0;
array<int, 101> schedule;
array<bool, 101> multitap;

void Print();

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> n >> k;

	for (int i = 1; i <= k; ++i) {
		cin >> schedule[i];
	}

	int ans = 0;
	for (int i = 1; i <= k; ++i) {
		// 이미 꽂혀 있다면
		if (multitap[schedule[i]]) {
			continue;
		}
		// 멀티탭에 빈자리가 있다면
		else if (multitapCount < n) {
			++multitapCount;
			multitap[schedule[i]] = true;
		}
		// 다른 것을 빼야할 경우 가장 나중에 사용될 것을 찾아 뽑는다.
		else {
			int offIndex = -1;
			int maxUseTime = 0;
			for (int j = 1; j <= k; ++j) {
				// 멀티탭에 꽂혀 있으면
				if (multitap[j]) {
					// 언제 사용되는지 확인한다.
					int useTime = numeric_limits<int>::max();
					for (int time = i + 1; time <= k; ++time) {
						if (schedule[time] == j) {
							useTime = time;
							break;
						}
					}
					
					// 더 나중에 사용될 경우 뽑는 플래그로 갱신해준다.
					if (useTime > maxUseTime) {
						maxUseTime = useTime;
						offIndex = j;
					}
				}
			}
			
			// offIndex 플래그를 뽑고 새로운 플래그를 꼽는다.
			multitap[offIndex] = false;
			multitap[schedule[i]] = true;
			++ans;

		}

		//Print();

	}

	cout << ans;

}

void Print() {
	cout << "\n";
	for (int i = 1; i <= k; ++i) {
		if (multitap[i])
			cout << i << " ";
	}
	cout << "\n";
}
