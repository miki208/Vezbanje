
#ifndef _ATOM_H_
#define _ATOM_H_

#include "AtomicFormula.h"

class Atom : public AtomicFormula
{
	public:
	Atom(unsigned);
	void print(std::ostream&) const;
	Type getType() const;
	bool equalsTo(const Formula&) const;
	void getAtoms(AtomSet&) const;
	bool eval(const Valuation&) const;
	private:
	unsigned id;
};

#endif
