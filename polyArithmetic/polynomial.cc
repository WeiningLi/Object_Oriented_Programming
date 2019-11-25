#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include "rational.h"
#include "polynomial.h"
using namespace std;

Polynomial::Polynomial() {
	coeffs = new Rational[1];
	capacity = 1;
}

Polynomial::~Polynomial() { 
	if(coeffs) delete[] coeffs;
}

Polynomial::Polynomial (const Polynomial &other) {
	capacity = other.capacity;
	coeffs = new Rational[capacity];
	for (int index = 0; index < capacity; ++index) {
		coeffs[index].num = other.coeffs[index].num;
		coeffs[index].den = other.coeffs[index].den;
	}
}

Polynomial::Polynomial(Polynomial &&other) {
	/*using std::swap;
	swap(capacity, other.capacity);
	swap(coeffs, other.coeffs);*/
	capacity = other.capacity;
	coeffs = other.coeffs;
	other.coeffs = nullptr;
}

Polynomial & Polynomial::operator=(const Polynomial &other) {
	if (this == &other) return *this;
	capacity = other.capacity;
	Rational *tmp = coeffs;
	coeffs = new Rational[capacity];
	delete[] tmp;
	for (int index = 0; index < capacity; ++index) {
		coeffs[index].num = other.coeffs[index].num;
		coeffs[index].den = other.coeffs[index].den;
	}
	return *this;
}

Polynomial & Polynomial::operator=(Polynomial &&other) {
	capacity = other.capacity;
	coeffs = other.coeffs;
	other.coeffs = nullptr;
	return *this;
}

Polynomial Polynomial::operator+(const Polynomial &rhs) const {
	Polynomial newP;
	if (capacity > rhs.capacity) {
		newP.capacity = capacity;
		Rational *tmp = newP.coeffs;
		newP.coeffs = new Rational[newP.capacity];
		for (int i = 0; i < rhs.capacity; ++i) {
			newP.coeffs[i] = coeffs[i] + rhs.coeffs[i];
		}
		for (int i = rhs.capacity; i < newP.capacity; ++i) {
			newP.coeffs[i] = coeffs[i];
		}
		delete[] tmp;
	}
	else {
		newP.capacity = rhs.capacity;
		Rational *tmp = newP.coeffs;
		newP.coeffs = new Rational[newP.capacity];
		for (int i = 0; i < capacity; ++i) {
			newP.coeffs[i] = coeffs[i] + rhs.coeffs[i];
		}
		for (int i = capacity; i < newP.capacity; ++i) {
			newP.coeffs[i] = rhs.coeffs[i];
		}
		delete[] tmp;
	}
	return newP;
}

Polynomial Polynomial::operator-(const Polynomial &rhs) const {
	Polynomial newP;
	if (capacity > rhs.capacity) {
		newP.capacity = capacity;
		Rational *tmp = newP.coeffs;
		newP.coeffs = new Rational[newP.capacity];
		for (int i = 0; i < rhs.capacity; ++i) {
			newP.coeffs[i] = coeffs[i] - rhs.coeffs[i];
		}
		for (int i = rhs.capacity; i < newP.capacity; ++i) {
			newP.coeffs[i] = coeffs[i];
		}
		delete[] tmp;
	}
	else {
		newP.capacity = rhs.capacity;
		Rational *tmp = newP.coeffs;
		newP.coeffs = new Rational[newP.capacity];
		for (int i = 0; i < capacity; ++i) {
			newP.coeffs[i] = coeffs[i] - rhs.coeffs[i];
		}
		for (int i = capacity; i < newP.capacity; ++i) {
			newP.coeffs[i] = -rhs.coeffs[i];
		}
		delete[] tmp;
	}
	return newP;
}

Polynomial Polynomial::operator*(const Polynomial &rhs) const {
	Polynomial newP;
	int max1 = degree();
	int max2 = rhs.degree();
	newP.capacity = max1 + max2 + 1;
	Rational *tmp = newP.coeffs;
	newP.coeffs = new Rational[newP.capacity];
	for (int i = 0; i < newP.capacity; ++i) {
		Rational tmp;
		for (int j = 0; j < capacity; ++j) {
			for (int k = 0; k < rhs.capacity; ++k) {
				if (i == (j + k)) {
					newP.coeffs[i] += (coeffs[j] * rhs.coeffs[k]);
				}
			}
		}
	}
	delete[] tmp;
	return newP;
}

Polynomial Polynomial::operator/(const Polynomial &rhs) const {
	Polynomial newP;
	int d1 = degree();
	int currD = d1;
	int d2 = rhs.degree();
	if (d1 < d2 || ((d1 == 0) && (coeffs[0].num == 0))) {
		return newP;
	}
	else {
		Rational currQ;
		Polynomial copy = *this;
		newP.capacity = d1 - d2 + 1;
		int currIndex = d1 - d2;
		Rational *tmp = newP.coeffs;
		newP.coeffs = new Rational[newP.capacity];
		Polynomial myTmp;
		delete[] tmp;
		while (currD >= d2) {
			currQ = (copy.coeffs[currD] / rhs.coeffs[d2]);
			tmp = myTmp.coeffs;
			myTmp.capacity = currD - d2 + 1;
			myTmp.coeffs = new Rational[myTmp.capacity];
			delete[] tmp;
			myTmp.coeffs[myTmp.capacity - 1] = currQ;
			--currD;
			copy = (copy - (myTmp * rhs));
			newP.coeffs[currIndex] = currQ;
			--currIndex;
		}
	}
	return newP;
}

Polynomial Polynomial::operator%(const Polynomial &rhs) const {
	Polynomial newP;
	newP = ((*this) - (rhs * (*this / rhs)));
	int deg;
	if (rhs.degree() == 0) deg = 0;
	else deg = rhs.degree();
	for (int i = deg; i < newP.capacity; ++i) {
		newP.coeffs[i].num = 0;
	}
	return newP;
}

int Polynomial::degree() const {
	int max = 0;
	for (int index = 0; index < capacity; ++index) {
		if (coeffs[index].num != 0) max = index;
	}
	return max;
}

std::ostream& operator<<(std::ostream& out, const Polynomial &poly) {
	int first = 1;
	int zero = 1;
	for (int index = poly.capacity - 1; index >= 0; index--) {
		if (poly.coeffs[index].num != 0) {
			zero = 0;
			if (first == 0) out << " + ";
			out << "(" << poly.coeffs[index] << ")";
			if (index != 0 && index != 1) out << "x^" << index;
			else if (index == 1) out << "x";
			first = 0;
		}
	}
	if (zero == 1) out << 0;
	return out;
}

std::istream& operator>>(std::istream& in, Polynomial &poly) {
	Rational *newCoeffs = new Rational[1];
	int cap = 1;
	Rational tmp;
	string line;
	getline(in, line);
	stringstream iss;
	iss << line;
	int tempDeg;
	while (iss >> tmp) {
		iss >> tempDeg;
		if (tempDeg + 1 > cap) {
			Rational *copy = new Rational[tempDeg + 1];
			for (int i = 0; i < cap; ++i) {
				copy[i] = newCoeffs[i];
			}
			cap = tempDeg + 1;
			Rational *temp = newCoeffs;
			newCoeffs = new Rational[cap];
			delete[] temp;
			for (int i = 0; i < cap; ++i) {
				newCoeffs[i] = copy[i];
			}
			delete[] copy;
		}
		newCoeffs[tempDeg] = tmp;
	}
	Rational *tmp1 = poly.coeffs;
	poly.coeffs = newCoeffs;
	delete[] tmp1;
	poly.capacity = cap;
	return in;
}


