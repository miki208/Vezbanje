#include "Iff.h"
#include "True.h"
#include "False.h"
#include "Not.h"

using namespace std;

void Iff::print(ostream &ostr) const
{
	ostr << "(" << this->_op1 << " <=> " << this->_op2 << ")";
}

Type Iff::getType() const
{
	return T_IFF;
}

Formula Iff::substitute(const Formula &f1, const Formula &f2)
{
	if(this->equalsTo(f1))
		return f2;
	else
		return make_shared<Iff>(this->_op1->substitute(f1, f2), this->_op2->substitute(f1, f2));
}


bool Iff::eval(const Valuation &v) const
{
	return this->_op1->eval(v) == this->_op2->eval(v);
}


Formula Iff::simplify()
{
	Formula simpl1 = this->_op1->simplify();
	Formula simpl2 = this->_op2->simplify();

	if(simpl1->getType() == T_FALSE && simpl2->getType() == T_FALSE)
		return make_shared<True>(); //this case is needed because: FALSE <=> anything = ¬(anything), so it's: FALSE <=> FALSE = ¬FALSE
	else if(simpl1->getType() == T_TRUE)
		return simpl2;
	else if(simpl2->getType() == T_TRUE)
		return simpl1;
	else if(simpl1->getType() == T_FALSE)
		return make_shared<Not>(simpl2);
	else if(simpl2->getType() == T_FALSE)
		return make_shared<Not>(simpl1);
	else
		return make_shared<Iff>(simpl1, simpl2);
}
