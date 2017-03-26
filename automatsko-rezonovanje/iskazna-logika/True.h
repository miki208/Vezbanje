#ifndef _TRUE_H_
#define _TRUE_H_

#include "LogicConstant.h"

class True : public LogicConstant
{
	public:
	Type getType() const;
	void print(std::ostream&) const;
	bool eval(const Valuation&) const;
};

#endif
