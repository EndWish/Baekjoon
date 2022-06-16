#include <iostream>
#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <sstream>

using namespace std;

string input;
int n;
vector<string> v;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//최기화,입력값 받기
	cin >> input >> n;
	v.assign(n, "");
	for (string& s : v)
		cin >> s;

	//문제해결
	vector<string> split;
	bool startFix = *input.begin() != '*';
	bool endFix = *input.rbegin() != '*';

	istringstream ss(input);
	string strBuffer;
	while (getline(ss, strBuffer, '*')) {
		if (!strBuffer.empty()) {
			split.push_back(move(strBuffer));
			strBuffer.clear();
		}
	}

	//cout << "\n";
	//cout << split.size() << "\n";
	//for (const string& s : split) {
	//	cout << s << " ";
	//}
	//cout << "\n";

	for (const string& fileName : v) {
		// *으로 시작하는지 확인
		if (startFix && !fileName.starts_with(*split.begin()) )	// 해당하는 문자로 시작하지 않을 경우
			continue;
		if (endFix && !fileName.ends_with(*split.rbegin()))	// 해당하는 문자로 끝나지 않을 경우
			continue;

		bool satisfy = true;
		
		auto begPos = fileName.begin();
		for (const string& findTarget : split) {
			//ranges::find(begPos, fileName.end(), findTarget);
			auto [b, e] = ranges::search(begPos, fileName.end(), findTarget.begin(), findTarget.end());
			if (b == fileName.end()) {	// 찾는 단어가 없다.
				satisfy = false;
				break;
			}
			else {	//찾는 단어가 있을 경우
				begPos = e;
			}
		}

		if (satisfy)
			cout << fileName << "\n";

	}

	//출력

}