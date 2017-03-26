#include "AtomicFormula.h"

using namespace std;

int AtomicFormula::complexity() const
{
	return 0;
}

Formula AtomicFormula::substitute(const Formula &a, const Formula &b)
{
	if(this->equalsTo(a))
		return b;
	else
		return shared_from_this();
}

