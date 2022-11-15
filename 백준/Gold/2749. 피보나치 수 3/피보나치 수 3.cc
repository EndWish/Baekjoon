#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <memory>
#include <cmath>

using namespace std;

#define MOD 1'000'000
#define ll long long

class Matrix {
public:
	
	int r, c;
	vector<vector<ll>> mat;

	Matrix() { }
	~Matrix() { };
	Matrix(int _r, int _c) {
		r = _r;
		c = _c;
		mat.assign(r, vector<ll>(c, {}));	// 0으로 초기화
	}
	Matrix(int _r, int _c, const initializer_list<ll>& _list) : Matrix(_r, _c) {
		SetNums(_list);
	}
	static Matrix Identity(int _size) {
		Matrix newMatrix(_size, _size);
		for (int i = 0; i < _size; ++i)
			newMatrix.mat[i][i] = 1;
		return newMatrix;
	}

	Matrix operator*(const Matrix& other) {
		if (c != other.r)
			cout << "행렬 곱 오류\n";

		Matrix newMatrix(r, other.c);
		for (int z = 0; z < c; ++z) {
			for (int y = 0; y < r; ++y) {
				for (int x = 0; x < other.c; ++x) {
					newMatrix.mat[y][x] += mat[y][z] * other.mat[z][x];
					newMatrix.mat[y][x] %= MOD;
				}
			}
		}
		return newMatrix;
	}

	void SetNums(const initializer_list<ll>& _list) {
		auto it = _list.begin();
		for (int y = 0; y < r; ++y) {
			for (int x = 0; x < c; ++x) {
				mat[y][x] = *it % MOD;
				++it;
			}
		}		
	}

	Matrix Pow(ll e) {
		if (e == 0)
			return Identity(r);
		if (e == 1)
			return *this;

		if (e & 1) {	// 홀수일 경우
			return ((*this) * (*this)).Pow(e / 2)* (*this);
		}
		else {	// 짝수일 경우
			return  ((*this) * (*this)).Pow(e / 2);
		}
	}

	void Print() {
		for (int y = 0; y < r; ++y) {
			for (int x = 0; x < c; ++x) {
				cout << mat[y][x] << " ";
			}
			cout << "\n";
		}
	}
	ll GetNum(int _r, int _c) {
		return mat[_r][_c];
	}
};

ll n;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	//초기화,입력값 받기
	cin >> n;

	//문제해결
	Matrix vec(1, 2, { 1,0 });
	Matrix transform(2, 2, { 1,1,1,0 });
	Matrix resultMatrix = vec * transform.Pow(n - 1);
	cout << resultMatrix.GetNum(0, 0);

	//출력

}