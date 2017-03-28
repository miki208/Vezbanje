#include "Or.h"
#include "True.h"

using namespace std;

void Or::print(ostream &ostr) const
{
	ostr << "(" << _op1 << " \\/ " << _op2 << ")";
}

Type Or::getType() const
{
	return T_OR;
}

Formula Or::substitute(const Formula &f1, const Formula &f2)
{
	if(equalsTo(f1))
		return f2;
	else
		return make_shared<Or>(_op1->substitute(f1, f2), _op2->substitute(f1, f2));
}


bool Or::eval(const Valuation &v) const
{
	return _op1->eval(v) || _op2->eval(v);
}


Formula Or::simplify()
{
	Formula simpl1 = _op1->simplify();
	Formula simpl2 = _op2->simplify();

	if(simpl1->getType() == T_TRUE || simpl2->getType() == T_TRUE)
		return make_shared<True>();
	else if(simpl1->getType() == T_FALSE)
		return simpl2;
	else if(simpl2->getType() == T_FALSE)
		return simpl1;
	else
		return make_shared<Or>(simpl1, simpl2);
}

Formula Or::nnf()
{
	return make_shared<Or>(_op1->nnf(), _op2->nnf());
}

LiteralListList Or::cnf()
{
	LiteralListList cnf1 = _op1->cnf();
	LiteralListList cnf2 = _op2->cnf();

	return cartesianProduct(cnf1, cnf2);
}

LiteralListList Or::dnf()
{
	LiteralListList dnf1 = _op1->dnf();
	LiteralListList dnf2 = _op2->dnf();

	return concatLists(dnf1, dnf2);
}
