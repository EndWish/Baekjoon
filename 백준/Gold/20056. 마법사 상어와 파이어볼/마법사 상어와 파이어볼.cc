#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

int N, M, K;

class FireBall;

array<array<array<vector<FireBall>, 51>, 51>, 2> board;	// 50x50짜리 판을 2개 만든다.
int curBoard = 0, nextBoard = 1;

int dr[] = { -1, -1,0,1,1,1,0,-1 };
int dc[] = { 0, 1,1,1,0,-1,-1,-1 };

class FireBall {
public:
	int r, c;	// 위치
	int m, s, d;	// 질량, 방향, 속도

	// 생성자
	FireBall(int r, int c, int m, int s, int d) : r{ r }, c{ c }, m{ m }, s{ s }, d{ d } {
	
	}

	void Move() {
		r = (r + dr[d] * s - 1 + N * 1000) % N + 1;
		c = (c + dc[d] * s - 1 + N * 1000) % N + 1;
		board[nextBoard][r][c].push_back(*this);
	}

};

void BoardPrint();

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N >> M >> K;

	// M개의 파이어볼을 입력받아 board에 넣는다.
	for (int i = 0; i < M; ++i) {
		int r, c, m, s, d;
		cin >> r >> c >> m >> s >> d;
		board[curBoard][r][c].emplace_back(r, c, m, s, d);
	}

	// BoardPrint();	// Text용 출력

	// K번 이동 명령을 한다.
	for (int cmd = 0; cmd < K; ++cmd) {

		// 1. 모든 파이어볼이 자신의 방향 di로 속력 si칸 만큼 이동한다.
		for (int r = 1; r <= N; ++r) {
			for (int c = 1; c <= N; ++c) {
				for (FireBall& fireBall : board[curBoard][r][c])
					fireBall.Move();
				board[curBoard][r][c].clear();
			}
		}

		// 파이어볼을 전부 nextBoard로 옮겼으므로 curBoard와 nextBoard를 바꿔준다.
		swap(nextBoard, curBoard);
		

		// 이동이 모두 끝난 뒤, 2개 이상의 파이어볼이 있는 칸에서는 다음과 같은 일이 일어난다.
		for (int r = 1; r <= N; ++r) {
			for (int c = 1; c <= N; ++c) {

				int nFireBall = board[curBoard][r][c].size();	// 파이어볼의 개수를 저장한다.
				
				// 파이어 볼이 2개 이상일 경우
				if (2 <= nFireBall) {
					int sumMass = 0, sumSpeed = 0;
					int dirType = 0;	// 0이면 0,2,4,6	1이면 1,3,5,7

					// 현재 칸에 있는 파이어볼들의 정보를 종합한다.
					for (int i = 0; i < nFireBall; ++i) {
						FireBall& fireBall = board[curBoard][r][c][i];
						sumMass += fireBall.m;
						sumSpeed += fireBall.s;
						if (0 < i) {	// 이전 파이어 볼과 홀짝이 맞지 않는다면 dirType을 1로 바꾼다.
							FireBall& prevFireBall = board[curBoard][r][c][i - 1];
							if (prevFireBall.d % 2 != fireBall.d % 2)
								dirType = 1;
						}
					}

					// 현재칸에 있는 파이어볼들을 없애고 새로운 4개의 파이어볼을 생성한다.
					board[curBoard][r][c].clear();
					if (sumMass / 5 > 0) {	// 질량이 0보다 클때만 생성한다.
						for (int i = 0; i < 4; ++i) {
							board[curBoard][r][c].emplace_back(r, c, sumMass / 5, sumSpeed / nFireBall, dirType + i * 2);
						}
					}

				}
			}
		}

		// Text용 출력
		//cout << "\n";
		//BoardPrint();

	}

	// 남아있는 파이어볼의 질량의 합을 구한다.
	int ans = 0;
	for (int r = 1; r <= N; ++r) {
		for (int c = 1; c <= N; ++c) {
			for (FireBall& fireBall : board[curBoard][r][c])
				ans += fireBall.m;
		}
	}

	cout << ans;

}

void BoardPrint() {
	for (int r = 1; r <= N; ++r) {
		for (int c = 1; c <= N; ++c) {
			cout << board[curBoard][r][c].size() << " ";
		}
		cout << "\n";
	}

}
