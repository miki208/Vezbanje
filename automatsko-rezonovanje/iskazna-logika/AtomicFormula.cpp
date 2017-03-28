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
