#ifndef _BINARY_CONNECTIVE_H_
#define _BINARY_CONNECTIVE_H_

#include "Formula.h"

class BinaryConnective : public BaseFormula
{
	public:
	BinaryConnective(const Formula&, const Formula&);
	int complexity() const;
	bool equalsTo(const Formula&) const;
	void getAtoms(AtomSet&) const;
	protected:
	Formula _op1;
	Formula _op2;
};

#endif
