#include <iostream>
#include <algorithm>
#include <array>
#include <vector>

using namespace std;

array <vector<vector<int>>, 7> block = {
	
	vector<vector<int>>{	// 1번
		vector<int>{0},			// -> 회전한 모양에 따른 왼쪽부터 높이의 값
		vector<int>{0,0,0,0},
	},
		
	vector<vector<int>>{	// 2번
		vector<int>{0,0},
	},

	vector<vector<int>>{	// 3번
		vector<int>{0,0,1},
		vector<int>{1,0},
	},
	
	vector<vector<int>>{	// 4번
		vector<int>{1,0,0},
		vector<int>{0,1},
	},

	vector<vector<int>>{	// 5번
		vector<int>{0,0,0},
		vector<int>{0,1},
		vector<int>{1,0,1},
		vector<int>{1,0},
	},

	vector<vector<int>>{	// 6번
		vector<int>{0,0,0},
		vector<int>{0,0},
		vector<int>{0,1,1},
		vector<int>{2,0},
	},

	vector<vector<int>>{	// 7번
		vector<int>{0,0,0},
		vector<int>{0,2},
		vector<int>{1,1,0},
		vector<int>{0,0},
	},
};
int c, p;
array<int, 100> hight;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> c >> p;
	p -= 1;
	for (int i = 0; i < c; ++i)
		cin >> hight[i];

	//문제해결
	int ans = 0;
	for (int x = 0; x < c; ++x) {	// 가로로 진행하면서
		for (int r = 0; r < block[p].size(); ++r) {	// 블록의 회전했을때 경우의 수만큼

			if (c <= x + block[p][r].size() - 1)	// 블럭이 범위 밖을 넘어가면 컨티뉴
				continue;

			bool success = true;
			
			int value = hight[x] - block[p][r][0];
			for (int blockX = 0; blockX < block[p][r].size(); ++blockX) {
				if (hight[x + blockX] - block[p][r][blockX] != value) {
					success = false;
					break;
				}
			}

			if (success)
				++ans;

		}
	}
	
	//출력
	cout << ans;

}