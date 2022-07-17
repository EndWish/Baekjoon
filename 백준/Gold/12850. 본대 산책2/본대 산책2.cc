#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#define ll long long
#define DIV 1'000'000'007LL

using namespace std;

class Mat {
public:
	Mat(int r, int c) : r{ r }, c{ c } {
		mat.assign(r, vector<ll>(c, 0LL));
	}

	Mat(int r, int c, ll* arr) : r{ r }, c{ c } {
		mat.assign(r, vector<ll>(c, 0));
		for (vector<ll>& row : mat) {
			copy(arr, arr + c, row.begin());
			for (ll& e : row)
				e %= DIV;
			arr += c;
		}
	}

	Mat operator*(const Mat& rhs) const {
		Mat res(r, rhs.c);

		for (int nr = 0; nr < r; ++nr)
			for (int nc = 0; nc < rhs.c; ++nc)
				for (int i = 0; i < c; ++i)
					res.mat[nr][nc] = (res.mat[nr][nc] + mat[nr][i] * rhs.mat[i][nc]) % DIV;

		return res;
	}

	Mat Pow(int p) {
		if (p == 1)
			return *this;

		if (p & 1) {	//홀수일 경우
			return ((*this) * (*this)).Pow(p / 2) * (*this);
		}
		else {	// 짝수일 경우
			return ((*this) * (*this)).Pow(p / 2);
		}
			
	}

	int GetElement(int row, int col) {
		return mat[row][col];
	}

	void Print() {
		for (vector<ll>& row : mat) {
			for (int e : row)
				cout << e << " ";
			cout << "\n";
		}
	}

private:
	vector<vector<ll>> mat;
	int r, c;
};

int d;

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);	

	//최기화,입력값 받기
	cin >> d;

	//문제해결
	// 행렬의 제곱(분할정복)을 이용하여 푼다.
  //a,b,c,d,e,f,g,h
	ll elements1[] = {
	0,1,1,0,0,0,0,0,// a
	1,0,1,1,0,0,0,0,// b
	1,1,0,1,0,1,0,0,// c
	0,1,1,0,1,1,0,0,// d
	0,0,0,1,0,1,1,0,// e
	0,0,1,1,1,0,0,1,// f
	0,0,0,0,1,0,0,1,// g
	0,0,0,0,0,1,1,0,// h
	};
	Mat mat(8, 8, elements1);

	ll elements2[] = { 1,0,0,0,0,0,0,0 };
	Mat vec(8, 1, elements2);

	//출력

	Mat resMatrix = mat.Pow(d) * vec;
	cout << resMatrix.GetElement(0, 0);
}
