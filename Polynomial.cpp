#include "Polynomial.h"
using namespace std;

// default constructor
Polynomial::Polynomial() {
	head = NULL;
}

// destructor
Polynomial::~Polynomial() {
	Node *p = head;
	while (p!=NULL) {
		Node *q = p;
		p = p->next;
		delete q->monom;
		delete q;
	}
}

Polynomial::Node* Polynomial::findGreaterOrEqual(int degree, Polynomial::Node*& prev) const {
	Node *ret = prev = NULL;
	Node *p = head;
	while (p && p->monom->getDegree() >= degree) {
		prev = ret;
		ret = p;
		p = p->next;
	}
	return ret;
}
void Polynomial::add(const Monomial &monom) {
	Node *prev;
	Node *p = findGreaterOrEqual(monom.getDegree(), prev);
	if (p && p->monom->getDegree() == monom.getDegree()) {
		p->monom->add(monom);
		if (p->monom->getCoefficient() == 0) { 
			delete p->monom;
			if (prev) {
				prev->next = p->next;
			}
			else {
				head = p->next;
			}
			delete p;
		}
	}
	else {
		Node *newNode = new Node;
		newNode->monom = new Monomial(monom);
		if (p) {
			newNode->next = p->next;
			p->next = newNode;
		}
		else {
			newNode->next = head;
			head = newNode;
		}
	}
}
void Polynomial::print() const {
	if (!head) {
		cout << "0";
	}
	else {
		Node *p = head;
		while (p) {
			if (p->monom->getCoefficient() > 0 && p != head) cout << '+';
			p->monom->print();
			p = p->next;
		}
	}
}

// getter and setter of the head
Polynomial::Node* Polynomial::getHead() const {
	return this->head;
}
void Polynomial::setHead(Polynomial::Node *& h)
{
	this->head = h;
}

// operators overloading
void Polynomial::operator=(const Polynomial &pol){
	Node *p = this->head;
	while (p)
	{
		Node* a = p;
		p = p->next;
		delete a->monom;
		delete a;
	}
	this->head = NULL;
	Polynomial::Node *curr_node = pol.getHead();
	while (curr_node!=NULL)
	{
		this->add(*(curr_node->monom));
		curr_node = curr_node->next;
	}
}
const Polynomial Polynomial::operator- (const Polynomial &pol)
{
	Polynomial *ans = new Polynomial;
	*ans = (*this);
	Polynomial::Node *curr_node;
	curr_node = pol.getHead();
	Monomial mon(-1, 0);
	while (curr_node != NULL)
	{
		ans->add((*(curr_node->monom))*mon);
		curr_node = curr_node->next;
	}
	return *ans;
}
const Polynomial Polynomial::operator- (const Monomial &mon)
{
	Polynomial *ans = new Polynomial;
	*ans = (*this);
	Monomial mon_neg(-1, 0);
	ans->add(mon_neg * mon);
	return *ans;
}
const Polynomial Polynomial::operator+ (const Polynomial &pol)
{
	Polynomial *ans = new Polynomial;
	*ans = (*this);
	Polynomial::Node *curr_node;
	curr_node = pol.getHead();
	while (curr_node != NULL)
	{
		ans->add(*(curr_node->monom));
		curr_node = curr_node->next;
	}
	return *ans;
}
const Polynomial Polynomial::operator+ (const Monomial &mon)
{
	Polynomial *ans = new Polynomial;
	*ans = (*this);
	ans->add(mon);
	return *ans;
}
void Polynomial::operator-=(const Monomial &mon)
{
	(*this) = (*this) - mon;
}
void Polynomial::operator-=(const Polynomial &pol)
{
	(*this) = (*this) - pol;
}
void Polynomial::operator+=(const Monomial &mon)
{
	(*this) = (*this) + mon;
}
void Polynomial::operator+=(const Polynomial &pol)
{
	(*this) = (*this) + pol;
}
void Polynomial::operator-() 
{
	Monomial mon(-1, 0);
	Polynomial::Node *curr_node;
	curr_node = this->head;
	while (curr_node != NULL)
	{
		*curr_node->monom = (*(curr_node->monom))*mon;
		curr_node = curr_node->next;
	}
}
bool Polynomial::operator==(const Polynomial &pol)
{
	Polynomial a;
	a = (*this);
	a -= pol;
	Node* curr = a.head;
	while (curr)
	{
		if (curr->monom->getCoefficient() != 0)
			return false;
		curr = curr->next;
	}
	return true;
}
bool Polynomial::operator!=(const Polynomial &pol)
{
	return !((*this) == pol);
}
bool Polynomial::operator!=(const Monomial &mon)
{
	Polynomial::Node* curr = this->getHead();
	if (*curr->monom == mon)
		return false;
	return true;
}
ostream & operator <<(ostream &buf, const Polynomial &pol) 
{
	Polynomial::Node *curr = pol.getHead();
	if (!curr)
		buf << "0";
	while (curr)
	{
		if (curr->monom->getCoefficient() > 0 && curr!=pol.head)
			buf << "+";
		buf << *curr->monom;
		curr = curr->next;
	}
	return buf;
}
istream & operator >>(istream &buf, Polynomial &pol) 
{
	Polynomial::Node *p = pol.getHead(), *n = NULL;
	while (p)
	{
		Polynomial::Node* a = p;
		p = p->next;
		delete a->monom;
		delete a;
	}
	pol.setHead(n);

	string polinom;
	int i = 0;
	getline(buf, polinom, '\n');
	int count = 0;
	for (int d = 0; polinom[d]!='\0'; d++)
		if (polinom[d] != ' ')
			polinom[count++] = polinom[d];
	polinom[count] = '\0';
	while (polinom[i] != '\0')
	{
		char* mon = new char[100];
		int j = 0, negsign = 1;
		if (polinom[i] == '-')
		{
			negsign = -1;
			i++;
		}
		if (polinom[i] == '+')
			i++;
		Monomial neg_sign(negsign, 0);
		while (polinom[i] != '\0' && polinom[i] != '+' && polinom[i] != '-')
		{
			mon[j++] = polinom[i++];
		}
		Monomial temp_mon;
		char* real_mon = new char[j+1];
		int k = 0;
		while (k < j)
			real_mon[k] = mon[k++];
		real_mon[j] = '\0';
		temp_mon = real_mon;;
		temp_mon *= neg_sign;
		pol += temp_mon;
	}
	if (!pol.getHead())
		pol += Monomial(0);
	return buf;
}
const double Polynomial::operator()(const double x) 
{
	Polynomial::Node *curr = this->getHead();
	double sum = 0;
	while (curr)
	{
		sum += (*curr->monom)(x);
		curr = curr->next;
	}
	return sum;
}
const double Polynomial::operator[](const int d) {
	Polynomial::Node *curr = this->getHead();
	while (curr)
	{
		if (curr->monom->getDegree() == d)
			return curr->monom->getCoefficient();
		curr = curr->next;
	}
	return 0;
}