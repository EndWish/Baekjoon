#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <initializer_list>

using namespace std;

#define ll long long
#define MOD 1'000'000'007LL

ll n;

class Matrix {
public:
	static Matrix Identity(int _rc);

protected:
	int r, c;
	vector<vector<ll>> nums;

public:
	Matrix() = default;
	Matrix(int _r, int _c);
	Matrix(int _r, int _c, initializer_list<ll> _nums);

	Matrix operator*(const Matrix& other) const;
	Matrix operator^(ll y) const;

	ll GetNum(int _r, int _c) const;

	void Print() const;

};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	//초기화,입력값 받기
	cin >> n;

	if (n & 1) {	// 홀수일 경우 가능한 경우가 없다.
		cout << 0;
		return 0;
	}

	//문제해결
	
	// a(i) = 4*a(i-2) -1*a(i-4)
	// (a2,a0) * M^((n-2)/2) = (an, an-2)		=> n이 짝수일 경우
	// M = (3, 1
	//		2, 0)

	

	Matrix transform(2, 2, { 4, 1, -1, 0 });
	Matrix v(1, 2, {3, 1});

	Matrix result = v * (transform ^ ((n - 2) / 2));
	cout << (result.GetNum(0, 0) + MOD) % MOD;
}

Matrix Matrix::Identity(int _rc) {
	Matrix result(_rc, _rc);
	for (int i = 0; i < _rc; ++i)
		result.nums[i][i] = 1LL;
	return result;
}

Matrix::Matrix(int _r, int _c) {
	r = _r;
	c = _c;
	nums.assign(r, vector<ll>(c, 0));
}

Matrix::Matrix(int _r, int _c, initializer_list<ll> _nums) : Matrix(_r, _c) {
	auto it = _nums.begin();
	for (int y = 0; y < r; ++y) {
		for (int x = 0; x < c; ++x) {
			nums[y][x] = *it % MOD;
			++it;
		}
	}
}

Matrix Matrix::operator*(const Matrix& other) const  {
	if (c != other.r)
		cout << "오류 : 행렬의 크기가 맞지 않다.\n";

	Matrix result(r, other.c);
	for (int y = 0; y < r; ++y) {
		for (int x = 0; x < other.c; ++x) {
			for (int z = 0; z < c; ++z) {
				result.nums[y][x] += nums[y][z] * other.nums[z][x];
				result.nums[y][x] %= MOD;
			}
		}
	}
	return result;
}

Matrix Matrix::operator^(ll y) const {
	const Matrix& self = *this;

	if (y == 0)
		return Matrix::Identity(r);

	if (y == 1)
		return self;

	if (y & 1) {	// 홀수일 경우
		return ((self * self) ^ (y / 2)) * self;
	}
	else {
		return (self * self) ^ (y / 2);
	}
}

ll Matrix::GetNum(int _r, int _c) const {
	return nums[_r][_c];
}

void Matrix::Print() const {
	for (int y = 0; y < r; ++y) {
		for (int x = 0; x < c; ++x) {
			cout << nums[y][x] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}
