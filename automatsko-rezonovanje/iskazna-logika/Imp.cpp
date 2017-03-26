#include "Imp.h"

using namespace std;

void Imp::print(ostream &ostr) const
{
	ostr << "(" << this->_op1 << " => " << this->_op2 << ")";
}

Type Imp::getType() const
{
	return T_IMP;
}

Formula Imp::substitute(const Formula &f1, const Formula &f2)
{
	if(this->equalsTo(f1))
		return f2;
	else
		return make_shared<Imp>(this->_op1->substitute(f1, f2), this->_op2->substitute(f1, f2));
}


bool Imp::eval(const Valuation &v) const
{
	return !this->_op1->eval(v) || this->_op2->eval(v);
}

