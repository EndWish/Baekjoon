#include <iostream>
#include <string>

using namespace std;

template<class T, class U>
std::pair<T, U> operator+(const std::pair<T, U>& l, const std::pair<T, U>& r) 
{
	return { l.first + r.first,l.second + r.second };
}

pair<int, int> king, stone;

int n;


pair<int, int> ChageCmdToXY(string& cmd);
bool Inside(pair<int, int> pos);
bool ExistStone(pair<int, int> pos);
void Print(pair<int, int> pos);

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	string input;
	cin >> input;
	king = { input[0] - 'A',input[1] - '1'};
	cin >> input;
	stone = { input[0] - 'A',input[1] - '1'};
	cin >> n;

	//문제해결
	for (int i = 0; i < n; ++i) {
		cin >> input;
		pair<int, int> move = ChageCmdToXY(input);

		pair<int, int> nextKingPos = { king + move };
		if (Inside(nextKingPos)) {
			// 이동할려는 곳에
			if (ExistStone(nextKingPos)) {
				//돌이 있는 경우
				if (Inside(stone + move)) {
					//밖으로 나가지 않는다면 밀어낸다.
					stone = stone + move;
					king = nextKingPos;
				}
			}
			else {
				//킹이동시 빈공간일 경우
				king = nextKingPos;
			}
		}
	}

	//출력
	Print(king);
	Print(stone);

}

pair<int, int> ChageCmdToXY(string& cmd) {
	if (cmd == "R")
		return { 1,0 };
	if (cmd == "L")
		return { -1,0 };
	if (cmd == "B")
		return { 0,-1 };
	if (cmd == "T")
		return { 0, 1 };
	if (cmd == "RT")
		return { 1,1 };
	if (cmd == "LT")
		return { -1,1 };
	if (cmd == "RB")
		return { 1,-1 };
	if (cmd == "LB")
		return { -1,-1 };
}

bool Inside(pair<int,int> pos) {
	if (pos.first < 0 || 8 <= pos.first || pos.second < 0 || 8 <= pos.second)
		return false;
	return true;
}

bool ExistStone(pair<int, int> pos) {
	if (stone == pos)
		return true;
	else
		return false;
}

void Print(pair<int, int> pos) 
{
	cout << (char)(pos.first + 'A') << pos.second + 1 << "\n";
}
