#include "And.h"
#include "False.h"

using namespace std;

void And::print(ostream &ostr) const
{
	cout << "(" << _op1 << " /\\ " << _op2 << ")";
}

Type And::getType() const
{
	return T_AND;
}

Formula And::substitute(const Formula &f1, const Formula &f2)
{
	if(equalsTo(f1))
		return f2;
	else
		return make_shared<And>(_op1->substitute(f1, f2), _op2->substitute(f1, f2));
}

bool And::eval(const Valuation &v) const
{
	return _op1->eval(v) && _op2->eval(v);
}

Formula And::simplify()
{
	Formula simpl1 = _op1->simplify();
	Formula simpl2 = _op2->simplify();

	if(simpl1->getType() == T_TRUE)
		return simpl2;
	else if(simpl2->getType() == T_TRUE)
		return simpl1;
	else if(simpl1->getType() == T_FALSE || simpl2->getType() == T_FALSE)
		return make_shared<False>();
	else
		return make_shared<And>(simpl1, simpl2);
}

Formula And::nnf()
{
	return make_shared<And>(_op1->nnf(), _op2->nnf());
}

LiteralListList And::cnf()
{
	LiteralListList cnf1 = _op1->cnf();
	LiteralListList cnf2 = _op2->cnf();

	return concatLists(cnf1, cnf2);
}

LiteralListList And::dnf()
{
	LiteralListList dnf1 = _op1->dnf();
	LiteralListList dnf2 = _op2->dnf();

	return cartesianProduct(dnf1, dnf2);
}
