#include "Formula.h"

using namespace std;

ostream& operator << (ostream &ostr, const Formula &f)
{
	f->print(ostr);
	return ostr;
}

bool BaseFormula::issat(Valuation &v) const
{
	AtomSet atoms;
	getAtoms(atoms);
	v.init(atoms);

	do {
		if(eval(v))
			return true;
	} while(v.next());

	return false;
}

bool BaseFormula::isTautology() const
{
	AtomSet atoms;
	getAtoms(atoms);
	Valuation v;
	v.init(atoms);

	do {
		if(!eval(v))
			return false;
	} while(v.next());

	return true;
}

void BaseFormula::printTruthTable() const
{
	AtomSet atoms;
	getAtoms(atoms);
	Valuation v;
	v.init(atoms);

	do {
		cout << v << " | " << eval(v) << endl;
	} while(v.next());
}

bool BaseFormula::isConsequence(const Formula &f) const
{
	AtomSet atoms;
	f->getAtoms(atoms);
	getAtoms(atoms);
	Valuation v;
	v.init(atoms);

	do {
		if(f->eval(v) && !eval(v))
			return false;
	} while(v.next());

	return true;
}

bool BaseFormula::isEquivalent(const Formula &f) const
{
	AtomSet atoms;
	f->getAtoms(atoms);
	getAtoms(atoms);
	Valuation v;
	v.init(atoms);

	do {
		if(f->eval(v) != eval(v))
			return false;
	} while(v.next());

	return true;
}
