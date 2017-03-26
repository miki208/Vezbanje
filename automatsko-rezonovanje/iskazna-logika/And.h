#ifndef _AND_H_
#define _AND_H_

#include "BinaryConnective.h"

class And : public BinaryConnective
{
	public:
	using BinaryConnective::BinaryConnective;
	void print(std::ostream&) const;
	Type getType() const;
	Formula substitute(const Formula&, const Formula&);
	bool eval(const Valuation&) const;
};

#endif
