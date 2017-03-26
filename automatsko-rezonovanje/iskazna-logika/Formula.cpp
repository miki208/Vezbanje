#include "Formula.h"

using namespace std;

ostream& operator << (ostream &ostr, const Formula &f)
{
	f->print(ostr);
	return ostr;
}

bool BaseFormula::issat() const
{
	AtomSet atoms;
	this->getAtoms(atoms);
	Valuation v;
	v.init(atoms);

	do {
		if(this->eval(v))
			return true;
	} while(v.next());

	return false;
}
