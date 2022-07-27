#include <iostream>
#include <stack>

#define pii pair<int,int>

using namespace std;

int n;
stack<pii> s;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> n;

	//문제해결
	long long ans = 0;

	int num;
	for (int i = 0; i < n; ++i) {
		cin >> num;

		int cnt = 0;
		while (!s.empty()) {
			if (s.top().first < num) {
				cnt += s.top().second;
				s.pop();
			}
			else {
				break;
			}
		}

		if (!s.empty()) {	// 비어있지 않을 경우
			if (s.top().first == num) {	// 마지막 수가 넣을 수와 같을 경우
				cnt += s.top().second;
				if (s.size() >= 2) {
					++cnt;
				}
				++s.top().second;
			}
			else {	// 마지막 수와 넣을 수가 같지 않을 경우
				++cnt;
				s.push({ num,1 });
			}
		}
		else {	// 비어있을 경우
			s.push({ num,1 });
		}

		ans += cnt;
		//cout << i << "번째 : +" << cnt << "\n";
	}

	//출력
	cout << ans;
	
}