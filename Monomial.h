#pragma once
#include <iostream>
#include <assert.h>
#include <string>


class Monomial {
public:
	Monomial(double coefficient = 1, int degree = 0);
	Monomial(const Monomial &other);
	~Monomial();
	bool add(const Monomial &other);
	double getCoefficient() const;
	int getDegree() const;
	void setCoefficient(double);
	void setDegree(int);
	void print() const;
	static int getNumberOfMonomials();
	void operator=(char*);
	void operator=(Monomial const &);
	const Monomial operator+(Monomial const &);
	const Monomial operator-(Monomial const &);
	const Monomial operator*(Monomial const &);
	const void operator*=(Monomial const &);
	const void operator-=(Monomial const &);
	const void operator+=(Monomial const &);
	const void operator-();
	bool operator==(Monomial const &);
	bool operator!=(Monomial const &);
	friend std::ostream & operator <<(std::ostream &buf, const Monomial &);
	friend std::istream & operator >> (std::istream &buf, Monomial &);
	const double operator()(double);
private:
	double coefficient;
	int degree;
	static int numberOfMonomials;
};