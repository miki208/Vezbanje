#include "UnaryConnective.h"

UnaryConnective::UnaryConnective(const Formula &f) : _op(f) { }

int UnaryConnective::complexity() const
{
	return 1 + _op->complexity();
}

bool UnaryConnective::equalsTo(const Formula &f) const
{
	return getType() == f->getType() && _op->equalsTo(((UnaryConnective*) f.get())->_op);
}

void UnaryConnective::getAtoms(AtomSet &atoms) const
{
	_op->getAtoms(atoms);
}

const Formula& UnaryConnective::getOp() const
{
	return _op;
}
