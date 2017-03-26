#ifndef _ATOMIC_FORMULA_H_
#define _ATOMIC_FORMULA_H_

#include "Formula.h"

class AtomicFormula : public BaseFormula
{
	public:
	int complexity();
	bool equalsTo(Formula&);
};

#endif
