#include <iostream>
#include <string>

using namespace std;

string name;
int age, weight;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	while (true) {
		//초기화,입력값 받기
		cin >> name >> age >> weight;
		if (name == "#" && age == 0 && weight == 0)
			break;

		//문제해결
		cout << name << " ";
		if (age > 17 || 80 <= weight)
			cout << "Senior";
		else
			cout << "Junior";
		cout << "\n";

		//출력
	}
}

