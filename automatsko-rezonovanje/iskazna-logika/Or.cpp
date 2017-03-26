#include "Or.h"

using namespace std;

void Or::print(ostream &ostr) const
{
	ostr << "(" << this->_op1 << " \\/ " << this->_op2 << ")";
}

Type Or::getType() const
{
	return T_OR;
}

Formula Or::substitute(const Formula &f1, const Formula &f2)
{
	if(this->equalsTo(f1))
		return f2;
	else
		return make_shared<Or>(this->_op1->substitute(f1, f2), this->_op2->substitute(f1, f2));
}


bool Or::eval(const Valuation &v) const
{
	return this->_op1->eval(v) || this->_op2->eval(v);
}
