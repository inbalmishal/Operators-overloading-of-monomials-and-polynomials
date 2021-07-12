#pragma once
#include <string>
#include <iostream>
#include "Monomial.h"
#include <string>

class Polynomial {
public:
	typedef struct node {
		Monomial *monom;
		struct node *next;
	} Node;
	Polynomial();
	~Polynomial();
	void add(const Monomial &);
	void print() const;
	void setHead(Node*&);
	Node* getHead() const;
	void operator=(const Polynomial &);
	const Polynomial operator- (const Polynomial &);
	const Polynomial operator- (const Monomial &);
	const Polynomial operator+ (const Polynomial &);
	const Polynomial operator+ (const Monomial &);
	void operator-=(const Monomial &);
	void operator-=(const Polynomial &);
	void operator+=(const Monomial  &);
	void operator+=(const Polynomial &);
	void operator-();
	bool operator==(const Polynomial  &);
	bool operator!=(const Polynomial &);
	bool operator!=(const Monomial &);
	friend std::ostream & operator <<(std::ostream &buf, const Polynomial &);
	friend std::istream & operator >> (std::istream &buf, Polynomial &);
	const double operator()(const double);
	const double operator[](const int);
private:
	Node *head;
	Node* findGreaterOrEqual(int degree, Node*& prev) const;
};