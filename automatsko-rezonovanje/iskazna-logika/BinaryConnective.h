#ifndef _BINARY_CONNECTIVE_H_
#define _BINARY_CONNECTIVE_H_

#include "Formula.h"

class BinaryConnective : public Formula
{
	public:
	BinaryConnective(const Formula&, const Formula&);
	protected:
	Formula _op1;
	Formula _op2;
};

#endif
