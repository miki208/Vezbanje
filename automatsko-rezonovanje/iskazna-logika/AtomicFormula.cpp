#include "AtomicFormula.h"

using namespace std;

int AtomicFormula::complexity()
{
	return 0;
}

bool AtomicFormula::equalsTo(Formula &f)
{
	return f->getType() == this->getType();
}
