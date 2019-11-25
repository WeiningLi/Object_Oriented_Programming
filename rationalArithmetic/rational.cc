#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include "rational.h"
using namespace std;

int getGcd(int num1, int num2) {
	return num2 == 0 ? num1 : getGcd(num2, num1 % num2);
}

void Rational::simplify() {
	int numNonNeg = 0;
	int denNonNeg = 0;
	if (num >= 0) {
		numNonNeg = 1;
	}
	else if (num < 0) {
		num = num * -1;
	}
	if (den > 0) {
		denNonNeg = 1;
	}
	else if (den < 0) {
		den = den * -1;
	}
	int gcd = getGcd(num, den);
	num = num / gcd;
	den = den / gcd;
	if (num != 0 && (numNonNeg + denNonNeg) == 1) {
		num *= -1;
	}
}

Rational::Rational(int num, int den) {
	this->num = num;
	this->den = den;
	(*this).simplify();
}

Rational Rational::operator+(const Rational &rhs) const {
	Rational r{ num * rhs.den + den * rhs.num, den * rhs.den };
	r.simplify();
	return r;
}
Rational Rational::operator-(const Rational &rhs) const {
	Rational r{ num * rhs.den - den * rhs.num, den * rhs.den };
	r.simplify();
	return r;
}

Rational Rational::operator*(const Rational &rhs) const {
	Rational r{ num * rhs.num, den * rhs.den };
	r.simplify();
	return r;
}

Rational Rational::operator/(const Rational &rhs) const {
	Rational r{ num * rhs.den, den * rhs.num };
	r.simplify();
	return r;
}

Rational & Rational::operator+=(const Rational &rhs) {
	num = num * rhs.den + rhs.num * den;
	den = den * rhs.den;
	(*this).simplify();
	return *this;
}

Rational & Rational::operator-=(const Rational &rhs) {
	num = num * rhs.den - rhs.num * den;
	den = den * rhs.den;
	(*this).simplify();
	return *this;
}

Rational Rational::operator-() const {
	Rational r{ num , den };
	r.simplify();
	if (r.num == 0) return r;
	else {
		r.num *= -1;
		return r;
	}
}

int Rational::getNumerator() const {
	return num;
}

int Rational::getDenominator() const {
	return den;
}

bool Rational::isZero() const {
	return num == 0;
}

std::ostream &operator<<(std::ostream &out, const Rational &rat) {
	out << rat.num;
	if (rat.den != 1) {
		out << "/" << rat.den;
	}
	return out;
}

std::istream &operator>>(std::istream &in, Rational &rat) {
	int n;
	char c;
	in >> n;
	rat.num = n;
	while (in >> c) {
		if (c == '/') break;
	}
	in >> n;
	rat.den = n;
	rat.simplify();
	return in;
}

