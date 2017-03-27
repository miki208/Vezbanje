#include "Or.h"
#include "True.h"
#include "False.h"

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


Formula Or::simplify()
{
	Formula simpl1 = this->_op1->simplify();
	Formula simpl2 = this->_op2->simplify();

	if(simpl1->getType() == T_TRUE || simpl2->getType() == T_TRUE)
		return make_shared<True>();
	else if(simpl1->getType() == T_FALSE)
		return simpl2;
	else if(simpl2->getType() == T_FALSE)
		return simpl1;
	else
		return make_shared<Or>(simpl1, simpl2);
}
