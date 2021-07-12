#pragma once
#include <iostream>
#include "Polynomial.h"
#include "Monomial.h"

using namespace std;

void testMonomial() {
	Monomial monom1, monom2;
	cout << "Monomial Test: (if you want to continue to polynomial test then enter m1=0 and m2=0) " << endl;
	do {
		cout << "\nEnter two monomials: " << endl;
		cin >> monom1 >> monom2;
		cout << "m1 = " << monom1 << ",m2 = " << monom2 << endl;
		cout << "m1 + m2 = " << monom1 + monom2 << endl;
		cout << "m1 - m2 = " << monom1 - monom2 << endl;
		cout << "m1 * m2= " << monom1 * monom2 << endl;
		monom1 *= 2;
		cout << "m1 *= 2, m1= " << monom1 << endl;
		monom2 += monom1;
		cout << "m2 += m1, m1 = " << monom1 << ", m2 = " << monom2 << endl;
	} while (monom1 != 0 || monom2 != 0);
}
void testPolynomial() {
	cout << "Polynomial Test:\n" << endl;
	cout << "test the default constructor:" << endl;
	Polynomial p;
	cout << "p = " << p << endl;
	cout << "add 1 to p" << endl;
	p += Monomial(1);
	cout << "p = " << p << endl;
	cout << "add x^2 to p" << endl;
	p += Monomial(1, 2);
	cout << "p = " << p << endl;
	cout << "add -x^2 to p" << endl;
	p += Monomial(-1, 2);
	cout << "p = " << p << endl;
	cout << "Number of Monomials = " << Monomial::getNumberOfMonomials() << endl;
	do {
		cout << "\nEnter a polynomial: (if you want to exit then enter 0)" << endl;
		cin >> p;
		cout << "p = " << p << endl;
		cout << "p(0) = " << p(0) << ", p(1) = " << p(1) << ", p(2) = " << p(2) << endl;
		cout << "p[0] = " << p[0] << ", p[1] = " << p[1] << ", p[2] = " << p[2] << ", p[4] = " << p[4] << endl;
		cout << "p + p = " << p + p << endl;
		cout << "Number of Monomials = " << Monomial::getNumberOfMonomials() << endl;
	} while (p != Monomial(0));
}
void main() {
	testMonomial();
	cout << "\n----------------------------------------------------------------------------------------------\n" << endl;
	testPolynomial();

	cout << "\nAt the end: Number of Monomials = " << Monomial::getNumberOfMonomials() << endl;
	system("PAUSE");
}