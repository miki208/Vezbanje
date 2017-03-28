#include "AtomicFormula.h"

using namespace std;

int AtomicFormula::complexity() const
{
	return 0;
}

Formula AtomicFormula::substitute(const Formula &a, const Formula &b)
{
	if(equalsTo(a))
		return b;
	else
		return shared_from_this();
}

Formula AtomicFormula::simplify()
{
	return shared_from_this();
}

Formula AtomicFormula::nnf()
{
	return shared_from_this();
}

LiteralListList AtomicFormula::cnf()
{
	if(getType() == T_ATOM)
		return { { shared_from_this() } };
	else if(getType() == T_TRUE)
		return { };
	else
		return { { } };
}

LiteralListList AtomicFormula::dnf()
{
	if(getType() == T_ATOM)
		return { { shared_from_this() } };
	else if(getType() == T_TRUE)
		return { { } };
	else
		return { };
}
