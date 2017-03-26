#include "BinaryConnective.h"

BinaryConnective::BinaryConnective(const Formula &f1, const Formula &f2) : _op1(f1), _op2(f2) { }

int BinaryConnective::complexity() const
{
	return 1 + _op1->complexity() + _op2->complexity();
}

bool BinaryConnective::equalsTo(const Formula &f) const
{
	return this->getType() == f->getType() && ((BinaryConnective*) f.get())->_op1->equalsTo(this->_op1)
						&& ((BinaryConnective*) f.get())->_op2->equalsTo(this->_op2);
}

void BinaryConnective::getAtoms(AtomSet &atoms) const
{
	this->_op1->getAtoms(atoms);
	this->_op2->getAtoms(atoms);
}
