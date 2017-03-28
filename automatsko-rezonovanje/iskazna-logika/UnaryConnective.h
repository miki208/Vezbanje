#ifndef _UNARY_CONNECTIVE_H_
#define _UNARY_CONNECTIVE_H_

#include "Formula.h"

class UnaryConnective : public BaseFormula
{
	public:
	UnaryConnective(const Formula&);
	int complexity() const;
	bool equalsTo(const Formula&) const;
	void getAtoms(AtomSet&) const;
	const Formula& getOp() const;
	protected:
	Formula _op;
};

#endif
