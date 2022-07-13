#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

#define MAXN 100

using namespace std;

int boardR, boardC, m;
int board[MAXN][MAXN];
int anglerX = -1;

class Shark {
public:
	int r, c;
	int speed;
	int dir;
	int size;

	bool operator<(const Shark& other) const {
		if (c == other.c) {
			if (r == other.r)
				return size > other.size;
			else
				return r < other.r;
		}
		else
			return c < other.c;
	}

	void Move() {
		int moving = speed;
		while (moving > 0) {
			if (dir == 1) {	// 위
				if (moving < r) {
					r -= moving;
					moving = 0;
				}
				else {
					moving -= r;
					r = 0;
					dir = 2;
				}
			}
			else if (dir == 2) {	// 아래
				if (moving < (boardR - 1) - r) {
					r += moving;
					moving = 0;
				}
				else {
					moving -= (boardR - 1) - r;
					r = boardR - 1;
					dir = 1;
				}
			}
			if (dir == 3) {	// 오른쪽
				if (moving < (boardC - 1) - c) {
					c += moving;
					moving = 0;
				}
				else {
					moving -= (boardC - 1) - c;
					c = boardC - 1;
					dir = 4;
				}
			}
			else if (dir == 4) {	// 왼쪽
				if (moving < c) {
					c -= moving;
					moving = 0;
				}
				else {
					moving -= c;
					c = 0;
					dir = 3;
				}
			}
		}


	}

	void Print() {
		cout << "(" << r << "," << c << "), size:" << size << "\n";
	}

};


vector<Shark> sharks;


int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> boardR >> boardC >> m;
	for (int i = 0; i < m; ++i) {
		Shark newShark;
		cin >> newShark.r >> newShark.c >> newShark.speed >> newShark.dir >> newShark.size;
		// r, c를 zero-base로 한다.
		newShark.r -= 1;
		newShark.c -= 1;
		sharks.push_back(newShark);
	}
	

	//문제해결
	int ans = 0;

	// 0. sharks는 r,c가 정렬된 상태를 가진다. c가 우선순위가 높다.
	ranges::sort(sharks, less<Shark>());

	while (true) {
		// 1. 낚시왕을 오른쪽으로 한 칸 이동
		if (++anglerX == boardC)	// 끝에 도달하면 끝낸다.
			break;

		// [검수]
		//cout << "낚시전:\n";
		//for (auto& s : sharks)
		//	s.Print();

		// 2. 낚시왕이 있는 열에 있는 상어 중에서 땅과 제일 가까운 상어를 잡는다. 상어를 잡으면 격자판에서 잡은 상어가 사라진다.
		auto fishing = ranges::lower_bound(sharks, anglerX, {}, &Shark::c);
		if (fishing != sharks.end() && fishing->c == anglerX) {	// 잡을 상어가 있을 경우
			// [검수]
			//cout << "낚음 : ";
			//fishing->Print();

			ans += fishing->size;
			sharks.erase(fishing);
		}

		// [검수]
		//cout << "낚시후:\n";
		//for (auto& s : sharks)
		//	s.Print();

		// 3. 상어가 이동하고, 정렬시켜 unique로 잡아먹는 것을 구현
		for (auto& s : sharks)
			s.Move();
		ranges::sort(sharks, less<Shark>());	

		// [검수]
		//cout << "이동후:\n";
		//for (auto& s : sharks)
		//	s.Print();

		auto p = ranges::unique(sharks, [](const Shark& a, const Shark& b) {
			if (a.r == b.r && a.c == b.c)
				return true;
			return false;
			});
		sharks.erase(p.begin(), p.end());

		// [검수]
		//cout << "잡아먹은후:\n";
		//for (auto& s : sharks)
		//	s.Print();

	}

	//출력
	cout << ans;

}