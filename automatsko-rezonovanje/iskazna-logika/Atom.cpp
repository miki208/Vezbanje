#include "Atom.h"

using namespace std;

Atom::Atom(unsigned id) : id(id) { };

void Atom::print(ostream &ostr) const
{
	ostr << "p" << id;
}

Type Atom::getType() const
{
	return T_ATOM;
}

bool Atom::equalsTo(const Formula &f) const
{
	return (this->getType() == f->getType()) && (this->id == ((Atom*) f.get())->id);
}

void Atom::getAtoms(AtomSet &atoms) const
{
	atoms.insert(this->id);
}

bool Atom::eval(const Valuation &v) const
{
	return v.getValue(this->id);
}
