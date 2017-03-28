#ifndef _OR_H_
#define _OR_H_

#include "BinaryConnective.h"

class Or : public BinaryConnective
{
	public:
	using BinaryConnective::BinaryConnective;
	void print(std::ostream&) const;
	Type getType() const;
	Formula substitute(const Formula&, const Formula&);
	bool eval(const Valuation&) const;
	Formula simplify();
	Formula nnf();
	LiteralListList cnf();
	LiteralListList dnf();
};

#endif
