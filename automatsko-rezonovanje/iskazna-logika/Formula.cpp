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

bool BaseFormula::isTautology() const
{
	AtomSet atoms;
	this->getAtoms(atoms);
	Valuation v;
	v.init(atoms);

	do {
		if(!this->eval(v))
			return false;
	} while(v.next());

	return true;
}

void BaseFormula::printTruthTable() const
{
	AtomSet atoms;
	this->getAtoms(atoms);
	Valuation v;
	v.init(atoms);

	do {
		cout << v << " | " << this->eval(v) << endl;
	} while(v.next());
}
