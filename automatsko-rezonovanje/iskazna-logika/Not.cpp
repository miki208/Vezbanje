#include "Not.h"
#include "False.h"
#include "True.h"

using namespace std;

void Not::print(ostream &ostr) const
{
	ostr << "(¬" << this->_op << ")";
}

Type Not::getType() const
{
	return T_NOT;
}

Formula Not::substitute(const Formula &f1, const Formula &f2)
{
	if(this->equalsTo(f1))
		return f2;
	else
		return make_shared<Not>(this->_op->substitute(f1, f2));
}

bool Not::eval(const Valuation &v) const
{
	return !this->_op->eval(v);
}

Formula Not::simplify()
{
	Formula simpl = this->_op->simplify();

	if(simpl->getType() == T_TRUE)
		return make_shared<False>();
	else if(simpl->getType() == T_FALSE)
		return make_shared<True>();
	else
		return make_shared<Not>(simpl);
}
