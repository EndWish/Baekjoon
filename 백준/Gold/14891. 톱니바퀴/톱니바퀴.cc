#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

class Gear {
private:
	array<int, 8> teath;

public:
	Gear() {
		teath.fill(0);
	}

	friend void operator>>(istream& in, Gear& gear) {
		for (int i = 0; i < 8; ++i) {
			char ch;
			in >> ch;
			gear.teath[i] = ch - '0';
		}
	}
	friend ostream& operator<<(ostream& os, const Gear& gear) {
		for (int i = 0; i < 8; ++i) {
			os << gear.teath[i];
		}
		return os;
	}

	int GetRight() {
		return teath[2];
	}
	int GetLeft() {
		return teath[6];
	}
	int GetUp() {
		return teath[0];
	}
	void Turn(int cmd) {
		if (cmd == 1) {	// 시계방향
			ranges::rotate(teath, teath.end() - 1);
		}
		else if (cmd == -1) {	// 반시계 방향
			ranges::rotate(teath, teath.begin() + 1);
		}
	}
};

array<Gear, 4> gears;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	for (int i = 0; i < 4; ++i) {
		cin >> gears[i];
	}

	//문제해결
	int k;
	cin >> k;
	while (k-- > 0) {
		array<int, 4> cmds;
		cmds.fill(0);

		int gearNum;
		cin >> gearNum;
		--gearNum;
		cin >> cmds[gearNum];

		// 오른쪽에 있는 톱니바퀴 확인
		int index = gearNum + 1;
		while (index <= 3) {
			if (gears[index - 1].GetRight() != gears[index].GetLeft()) {
				cmds[index] = cmds[index - 1] * -1;
				++index;
			}
			else {
				break;
			}
		}

		// 왼쪽에 있는 톱니바퀴 확인
		index = gearNum - 1;
		while (0 <= index) {
			if (gears[index].GetRight() != gears[index + 1].GetLeft()) {
				cmds[index] = cmds[index + 1] * -1;
				--index;
			}
			else {
				break;
			}
		}

		for (int i = 0; i < 4; ++i) {
			gears[i].Turn(cmds[i]);
			// 눈으로 확인해 보기
			//cout << gears[i] << "\n";
		}



	}

	int ans = 0;
	for (int i = 0; i < 4; ++i) {
		ans += (gears[i].GetUp() << i);
	}
	cout << ans;

}

