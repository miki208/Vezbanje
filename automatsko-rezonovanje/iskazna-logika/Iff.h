#ifndef _IFF_H_
#define _IFF_H_

#include "BinaryConnective.h"

class Iff : public BinaryConnective
{
	public:
	using BinaryConnective::BinaryConnective;
	void print(std::ostream&) const;
	Type getType() const;
	Formula substitute(const Formula&, const Formula&);
	bool eval(const Valuation&) const;
};

#endif
