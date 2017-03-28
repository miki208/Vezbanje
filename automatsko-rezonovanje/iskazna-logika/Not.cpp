#include "Not.h"
#include "False.h"
#include "True.h"
#include "And.h"
#include "Or.h"
#include "Imp.h"
#include "Iff.h"

using namespace std;

void Not::print(ostream &ostr) const
{
	ostr << "(¬" << _op << ")";
}

Type Not::getType() const
{
	return T_NOT;
}

Formula Not::substitute(const Formula &f1, const Formula &f2)
{
	if(equalsTo(f1))
		return f2;
	else
		return make_shared<Not>(_op->substitute(f1, f2));
}

bool Not::eval(const Valuation &v) const
{
	return !_op->eval(v);
}

Formula Not::simplify()
{
	Formula simpl = _op->simplify();

	if(simpl->getType() == T_TRUE)
		return make_shared<False>();
	else if(simpl->getType() == T_FALSE)
		return make_shared<True>();
	else
		return make_shared<Not>(simpl);
}

Formula Not::nnf()
{
	if(_op->getType() == T_NOT) {
		return ((Not*) _op.get())->_op->nnf();
	} else if(_op->getType() == T_AND) {
		And *tmp = (And*) _op.get();
		return make_shared<Or>(make_shared<Not>(tmp->getOp1())->nnf(), make_shared<Not>(tmp->getOp2())->nnf());
	} else if(_op->getType() == T_OR) {
		Or *tmp = (Or*) _op.get();
		return make_shared<And>(make_shared<Not>(tmp->getOp1())->nnf(), make_shared<Not>(tmp->getOp2())->nnf());
	} else if(_op->getType() == T_IFF) {
		Iff *tmp = (Iff*) _op.get();
		return make_shared<And>(make_shared<Or>(make_shared<Not>(tmp->getOp1())->nnf(), make_shared<Not>(tmp->getOp2())->nnf()),
				make_shared<Or>(tmp->getOp1()->nnf(), tmp->getOp2()->nnf()));
	} else if(_op->getType() == T_IMP) {
		Imp *tmp = (Imp*) _op.get();
		return make_shared<And>(tmp->getOp1()->nnf(), make_shared<Not>(tmp->getOp2())->nnf());
	} else {
		return shared_from_this();
	}
}

LiteralListList Not::cnf()
{
	return { { shared_from_this() } };
}

LiteralListList Not::dnf()
{
	return { { shared_from_this() } }; 
}
