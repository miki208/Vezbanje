#ifndef _FORMULA_H_
#define _FORMULA_H_

#include <memory>
#include <iostream>

class BaseFormula;

typedef std::shared_ptr<BaseFormula> Formula;

enum Type {T_TRUE, T_FALSE, T_AND, T_OR, T_NOT, T_IFF, T_IMP, T_ATOM};

class BaseFormula : public std::enable_shared_from_this<BaseFormula>
{
	public:
	virtual Type getType() = 0;
	virtual int complexity() = 0;
	virtual void print(std::ostream&) = 0;
	virtual bool equalsTo(Formula&) = 0;
};

std::ostream& operator << (std::ostream&, const Formula&);

#endif
