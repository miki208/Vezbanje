#include "BinaryConnective.h"

BinaryConnective::BinaryConnective(const Formula &f1, const Formula &f2) : _op1(f1), _op2(f2) { }

int BinaryConnective::complexity() const
{
	return 1 + _op1->complexity() + _op2->complexity();
}

bool BinaryConnective::equalsTo(const Formula &f) const
{
	return getType() == f->getType() && ((BinaryConnective*) f.get())->_op1->equalsTo(_op1)
						&& ((BinaryConnective*) f.get())->_op2->equalsTo(_op2);
}

void BinaryConnective::getAtoms(AtomSet &atoms) const
{
	_op1->getAtoms(atoms);
	_op2->getAtoms(atoms);
}

const Formula& BinaryConnective::getOp1() const
{
	return _op1;
}

const Formula& BinaryConnective::getOp2() const
{
	return _op2;
}
