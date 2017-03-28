#include "Iff.h"
#include "True.h"
#include "Not.h"
#include "And.h"
#include "Or.h"

using namespace std;

void Iff::print(ostream &ostr) const
{
	ostr << "(" << _op1 << " <=> " << _op2 << ")";
}

Type Iff::getType() const
{
	return T_IFF;
}

Formula Iff::substitute(const Formula &f1, const Formula &f2)
{
	if(equalsTo(f1))
		return f2;
	else
		return make_shared<Iff>(_op1->substitute(f1, f2), _op2->substitute(f1, f2));
}


bool Iff::eval(const Valuation &v) const
{
	return _op1->eval(v) == _op2->eval(v);
}


Formula Iff::simplify()
{
	Formula simpl1 = _op1->simplify();
	Formula simpl2 = _op2->simplify();

	if(simpl1->getType() == T_FALSE && simpl2->getType() == T_FALSE)
		return make_shared<True>(); //this case is needed because: FALSE <=> anything = ¬(anything), so it's: FALSE <=> FALSE = ¬FALSE
	else if(simpl1->getType() == T_TRUE)
		return simpl2;
	else if(simpl2->getType() == T_TRUE)
		return simpl1;
	else if(simpl1->getType() == T_FALSE)
		return make_shared<Not>(simpl2);
	else if(simpl2->getType() == T_FALSE)
		return make_shared<Not>(simpl1);
	else
		return make_shared<Iff>(simpl1, simpl2);
}

Formula Iff::nnf()
{
	return make_shared<Or>(make_shared<And>(make_shared<Not>(_op1)->nnf(), make_shared<Not>(_op2)->nnf()),
			make_shared<And>(_op1->nnf(), _op2->nnf()));
}

LiteralListList Iff::cnf()
{
	throw "Not applicable";
}

LiteralListList Iff::dnf()
{
	throw "Not applicable";
}
