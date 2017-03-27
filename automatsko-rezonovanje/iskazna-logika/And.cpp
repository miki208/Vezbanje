#include "And.h"
#include "True.h"
#include "False.h"

using namespace std;

void And::print(ostream &ostr) const
{
	cout << "(" << this->_op1 << " /\\ " << this->_op2 << ")";
}

Type And::getType() const
{
	return T_AND;
}

Formula And::substitute(const Formula &f1, const Formula &f2)
{
	if(this->equalsTo(f1))
		return f2;
	else
		return make_shared<And>(_op1->substitute(f1, f2), _op2->substitute(f1, f2));
}

bool And::eval(const Valuation &v) const
{
	return _op1->eval(v) && _op2->eval(v);
}

Formula And::simplify()
{
	Formula simpl1 = this->_op1->simplify();
	Formula simpl2 = this->_op2->simplify();

	if(simpl1->getType() == T_TRUE)
		return simpl2;
	else if(simpl2->getType() == T_TRUE)
		return simpl1;
	else if(simpl1->getType() == T_FALSE || simpl2->getType() == T_FALSE)
		return make_shared<False>();
	else
		return make_shared<And>(simpl1, simpl2);
}
