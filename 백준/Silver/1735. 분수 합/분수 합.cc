#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

#define ll long long

struct Fraction {
	ll numerator, denominator;

	Fraction operator+(const Fraction& other) const {
		Fraction result;
		result.denominator = this->denominator * other.denominator;
		result.numerator = this->numerator * other.denominator + this->denominator * other.numerator;
		ll div = gcd(result.denominator, result.numerator);
		result.numerator /= div;
		result.denominator /= div;
		return result;
	}
};

int main() {

	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	Fraction fraction[2];
	for (int i = 0; i < 2; ++i) {
		cin >> fraction[i].numerator >> fraction[i].denominator;
	}

	Fraction result = fraction[0] + fraction[1];
	cout << result.numerator << " " << result.denominator;

}

