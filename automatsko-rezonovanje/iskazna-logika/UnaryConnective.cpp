#include "UnaryConnective.h"

UnaryConnective::UnaryConnective(const Formula &f) : _op(f) { }

int UnaryConnective::complexity() const
{
	return 1 + this->_op->complexity();
}

bool UnaryConnective::equalsTo(const Formula &f) const
{
	return this->getType() == f->getType() && this->_op->equalsTo(((UnaryConnective*) f.get())->_op);
}

void UnaryConnective::getAtoms(AtomSet &atoms) const
{
	this->_op->getAtoms(atoms);
}
