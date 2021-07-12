#include "Monomial.h"

using namespace std;

// count how many monomials exist
int Monomial::numberOfMonomials = 0;

// regular constructor
Monomial::Monomial(double coefficient, int degree) : degree(degree) {
	assert(degree >= 0);
	this->coefficient = coefficient;
	numberOfMonomials++;
}

// copy constructor
Monomial::Monomial(const Monomial& other) : degree(other.degree) {
	this->coefficient = other.coefficient;
	numberOfMonomials++;
}

// destructor
Monomial::~Monomial() {
	numberOfMonomials--;
}

// getters
double Monomial::getCoefficient() const {
	return coefficient;
}
int Monomial::getDegree() const {
	return degree;
}
int Monomial::getNumberOfMonomials() {
	return numberOfMonomials;
}


// setters
void Monomial::setCoefficient(double c)
{
	this->coefficient = c;
}
void Monomial::setDegree(int d)
{
	this->degree = d;
}

// return true if it is possible to connect between the monomials
bool Monomial::add(const Monomial &other) {
	if (other.degree != degree) return false;
	coefficient += other.coefficient;
	return true;
}

// print the monomial
void Monomial::print() const {
	if (coefficient != 1 || degree == 0) cout << coefficient;
	if (coefficient != 1 && degree > 0) cout << "*";
	if (degree > 0) cout << "x";
	if (degree > 1) cout << "^" << degree;
}

// operators overloading
void Monomial::operator=(char* monom)
{
	int i = 0, d = 0 , neg = 1;
	double c = 0;
	int count = 0;

	// delete spaces in monom
	for (int d = 0; monom[d] != '\0'; d++)
		if (monom[d] != ' ')
			monom[count++] = monom[d];
	monom[count] = '\0';

	// check if the sign is '-'
	if (monom[i] == '-')
	{
		neg = -1;
		i++;
	}

	// while the organ in the monomial belongs to the coefficient
	while (monom[i] <= '9' && monom[i] >= '0')
	{
		c *= 10;
		c += (monom[i]-'0');
		i++;
	}

	// set the coefficient. if this is the end then the degree is d (=0).
	if (monom[i] == '\0')
	{
		this->coefficient = c*neg;
		this->degree = d;
	}
	else {
		// if the coefficient is 1 or -1
		if (i == 0 || (i == 1 && neg == -1))
			c = 1;
		// keep moving on the monomial until we are on a digit (on the degree).
		while (monom[i] != '\0' && (monom[i] > '9' || monom[i] < '0'))
			i++;
		if (monom[i] == '\0') // the degree is 1
		{
			d = 1;
			this->coefficient = c*neg;
			this->degree = d;
		}
		else {
			// get the degree
			while ((monom[i] <= '9' && monom[i] >= '0') && monom[i] != '\0')
			{
				d *= 10;
				d += (monom[i] - '0');
				i++;
			}
			// set the coefficient and the degree
			this->coefficient = c*neg;
			this->degree = d;
		}
	}
}
void Monomial::operator=(Monomial const &a)
{
	this->coefficient = a.getCoefficient();
	this->degree = a.getDegree();
}
const Monomial Monomial::operator+(Monomial const &a)
{
	if (this->degree != a.getDegree())
		return (*this);
	const Monomial ans = Monomial(a.getCoefficient() + this->coefficient, a.getDegree());
	return ans;
}
const Monomial Monomial::operator-(Monomial const &a)
{
	if (this->degree != a.getDegree())
		return (*this);
	const Monomial ans = Monomial(this->coefficient - a.getCoefficient(), a.getDegree());
	return ans;
}
const Monomial Monomial::operator*(Monomial const &a)
{
	const Monomial ans = Monomial(a.getCoefficient() * this->coefficient, a.getDegree() + this->degree);
	return ans;
}
const void Monomial::operator*=(Monomial const &a)
{
	(*this) = (*this) * a;
}
const void Monomial::operator-=(Monomial const &a)
{
	(*this) = (*this) - a;
}
const void Monomial::operator+=(Monomial const &a)
{
	(*this) = (*this) + a;
}
const void Monomial::operator-()
{
	this->coefficient *= -1;
}
bool Monomial::operator==(Monomial const &a) {
	if (this->coefficient == a.getCoefficient() && this->degree == a.getDegree())
		return true;
	return false;
}
bool Monomial::operator!=(Monomial const &a) {
	if (this->coefficient == a.getCoefficient() && this->degree == a.getDegree())
		return false;
	return true;
}
ostream &operator<<(ostream &buf, const Monomial &a)
{
	if (a.getCoefficient() != 1 || a.getDegree() == 0) buf << a.getCoefficient();
	if (a.getCoefficient() != 1 && a.getDegree() > 0) buf << "*";
	if (a.getDegree() > 0) buf << "x";
	if (a.getDegree() > 1) buf << "^" << a.getDegree();
	return buf;
}
istream &operator >> (istream &buf, Monomial &a)
{
	string monom;
	int i = 0, d = 0, neg = 1;
	double c = 0;

	getline(buf, monom, '\n');
	int count = 0;
	for (int d = 0; monom[d] != '\0'; d++)
		if (monom[d] != ' ')
			monom[count++] = monom[d];
	monom[count] = '\0';
	if (monom[i] == '-')
	{
		neg = -1;
		i++;
	}
	while (monom[i] <= '9' && monom[i] >= '0')
	{
		c *= 10;
		c += (monom[i] - '0');
		i++;
	}
	if (monom[i] == '\0') // if the monomial is only a number
	{
		a.setCoefficient(c*neg);
		a.setDegree(d);
		return buf;
	}
	if (i == 0 || (i == 1 && neg == -1))
		c = 1;
	while (monom[i] != '\0' && (monom[i] > '9' || monom[i] < '0'))
	{
		i++;
	}
	if (monom[i] == '\0')//if the monomial's degree is 1
	{
		d = 1;
		a.setCoefficient(c*neg);
		a.setDegree(d);
		return buf;
	}
	while ((monom[i] <= '9' && monom[i] >= '0') && monom[i] != '\0')
	{
		d *= 10;
		d += (monom[i] - '0');
		i++;
	}
	a.setCoefficient(c*neg);
	a.setDegree(d);
	return buf;
}
const double Monomial::operator()(double r) {
	double num = 1;
	for (int i = 0; i < this->degree; i++)
		num *= r;
	return (this->coefficient * num);
}