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

/***** Pomocne funkcije za rad sa listama *****/

LiteralListList concatLists(const LiteralListList &l1, const LiteralListList &l2)
{
	LiteralListList nl = l1;

	for(auto b = l2.begin(), e = l2.end(); b != e; b++)
		nl.push_back(*b);

	return nl;
}


LiteralList concatLists(const LiteralList &l1, const LiteralList &l2)
{
	LiteralList nl = l1;

	for(auto b = l2.begin(), e = l2.end(); b != e; b++)
		nl.push_back(*b);

	return nl;
}

LiteralListList cartesianProduct(const LiteralListList &l1, const LiteralListList &l2)
{
	LiteralListList nl;

	for(auto &e1 : l1)
		for(auto &e2 : l2)
			nl.push_back(concatLists(e1, e2));

	return nl;
}

std::ostream& operator << (std::ostream &ostr, const LiteralListList &l)
{
	ostr << "[ ";
	for(auto &i : l)
	{
		ostr << "[ ";
		for(auto &ii : i)
			ostr << ii << " ";
		ostr << "] ";
	}
	ostr << " ]";

	return ostr;
}
