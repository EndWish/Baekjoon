#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

class TriNode {
private:
	bool word;
	TriNode* a[26];

public:
	TriNode() {
		word = false;
		fill_n(&a[0], 26, nullptr);
	}

	TriNode* GetNext(char ch) {
		return a[ch - 'a'];
	}

	TriNode* SetNext(char ch) {
		char index = ch - 'a';
		if (a[index] == nullptr) {
			a[index] = new TriNode();
		}
		return a[index];
	}

	bool IsWord() {
		return word;
	}

	void SetWord() {
		word = true;
	}

};

int c, n, q;
TriNode root;
vector<string> nickNames;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> c >> n;
	string input;
	for (int i = 0; i < c; ++i) {
		cin >> input;
		TriNode* pos = &root;
		for (char ch : input) {
			pos = pos->SetNext(ch);
		}
		pos->SetWord();
	}

	nickNames.assign(n, {});
	for (string& nickName : nickNames)
		cin >> nickName;
	ranges::sort(nickNames);

	//문제해결
	cin >> q;
	for (int i = 0; i < q; ++i) {
		bool ans = false;

		cin >> input;
		TriNode* pos = &root;
		for (int j = 0; j < input.size(); ++j) {
			pos = pos->GetNext(input[j]);

			if (pos == nullptr)
				break;

			if (pos->IsWord()) {	// j까지가 색상에 해당하는 이름일 경우
				string nickName(input.begin() + j + 1, input.end());
				if (ranges::binary_search(nickNames, nickName)) {
					ans = true;
					break;
				}
			}
		}

		if (ans)
			cout << "Yes\n";
		else
			cout << "No\n";

	}

	//출력

}
