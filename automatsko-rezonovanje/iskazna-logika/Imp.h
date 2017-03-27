#ifndef _IMP_H_
#define _IMP_H_

#include "BinaryConnective.h"

class Imp : public BinaryConnective
{
	public:
	using BinaryConnective::BinaryConnective;
	void print(std::ostream&) const;
	Type getType() const;
	Formula substitute(const Formula&, const Formula&);
	bool eval(const Valuation&) const;
	Formula simplify();
	Formula nnf();
};

#endif

