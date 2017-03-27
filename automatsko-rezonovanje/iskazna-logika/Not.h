#ifndef _NOT_H_
#define _NOT_H_

#include "UnaryConnective.h"

class Not : public UnaryConnective
{
	public:
	using UnaryConnective::UnaryConnective;
	void print(std::ostream&) const;
	Type getType() const;
	Formula substitute(const Formula&, const Formula&);
	bool eval(const Valuation&) const;
	Formula simplify();	
};

#endif
