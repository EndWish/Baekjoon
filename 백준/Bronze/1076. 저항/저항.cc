#include <iostream>
#include <string>
#include <unordered_map>
#include <array>

#define pll pair<long long, long long>

using namespace std;

unordered_map<string, pll> color{
	make_pair("black"s,		make_pair(0, 1)),
	make_pair("brown"s,		make_pair(1, 10)),
	make_pair("red"s,		make_pair(2, 100)),
	make_pair("orange"s,	make_pair(3, 1'000)),
	make_pair("yellow"s,	make_pair(4, 10'000)),
	make_pair("green"s,		make_pair(5, 100'000)),
	make_pair("blue"s,		make_pair(6, 1'000'000)),
	make_pair("violet"s,	make_pair(7, 10'000'000)),
	make_pair("grey"s,		make_pair(8, 100'000'000)),
	make_pair("white"s,		make_pair(9, 1'000'000'000)),
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	array<string, 3> input;
	for (string& s : input)
		cin >> s;

	//문제해결
	long long ans = (color[input[0]].first * 10 + color[input[1]].first) * color[input[2]].second;

	//출력
	cout << ans;

}