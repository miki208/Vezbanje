#ifndef _FALSE_H_
#define _FALSE_H_

#include "LogicConstant.h"

class False : public LogicConstant
{
	public:
	Type getType() const;
	void print(std::ostream&) const;
	bool eval(const Valuation&) const;
};

#endif
