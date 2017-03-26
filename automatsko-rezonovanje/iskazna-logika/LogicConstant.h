#ifndef _LOGIC_CONSTANT_H_
#define _LOGIC_CONSTANT_H_

#include "AtomicFormula.h"

class LogicConstant : public AtomicFormula
{
	public:
	bool equalsTo(const Formula&) const;
	void getAtoms(AtomSet&) const;
};

#endif
