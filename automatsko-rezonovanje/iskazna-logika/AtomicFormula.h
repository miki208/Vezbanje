#ifndef _ATOMIC_FORMULA_H_
#define _ATOMIC_FORMULA_H_

#include "Formula.h"

class AtomicFormula : public BaseFormula
{
	public:
	int complexity() const;
	Formula substitute(const Formula&, const Formula&);	
	Formula simplify();
	Formula nnf();
};

#endif
