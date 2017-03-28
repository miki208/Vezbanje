#include "Imp.h"
#include "True.h"
#include "Not.h"
#include "Or.h"

using namespace std;

void Imp::print(ostream &ostr) const
{
	ostr << "(" << _op1 << " => " << _op2 << ")";
}

Type Imp::getType() const
{
	return T_IMP;
}

Formula Imp::substitute(const Formula &f1, const Formula &f2)
{
	if(equalsTo(f1))
		return f2;
	else
		return make_shared<Imp>(_op1->substitute(f1, f2), _op2->substitute(f1, f2));
}

bool Imp::eval(const Valuation &v) const
{
	return !_op1->eval(v) || _op2->eval(v);
}

Formula Imp::simplify()
{
	Formula simpl1 = _op1->simplify();
	Formula simpl2 = _op2->simplify();

	if(simpl2->getType() == T_TRUE || simpl1->getType() == T_FALSE)
		return make_shared<True>();
	else if(simpl1->getType() == T_TRUE)
		return simpl2;
	else if(simpl2->getType() == T_FALSE)
		return make_shared<Not>(simpl1);
	else
		return make_shared<Imp>(simpl1, simpl2);
}

Formula Imp::nnf()
{
	return make_shared<Or>(make_shared<Not>(_op1)->nnf(), _op2->nnf());
}

LiteralListList Imp::cnf()
{
	throw "Not applicable";
}

LiteralListList Imp::dnf()
{
	throw "Not applicable";
}
