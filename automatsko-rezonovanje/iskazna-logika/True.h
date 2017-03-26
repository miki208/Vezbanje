#ifndef _TRUE_H_
#define _TRUE_H_

#include "LogicConstant.h"

class True : public LogicConstant
{
	public:
	Type getType();
	void print(std::ostream&);
};

#endif
