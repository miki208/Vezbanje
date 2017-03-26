#include "Valuation.h"

using namespace std;

bool Valuation::getValue(unsigned id) const
{
	return _vars.find(id)->second;
}

void Valuation::setValue(unsigned id, bool v)
{
	_vars[id] = v;
}


void Valuation::init(const AtomSet &atoms)
{
	_vars.clear();

	for(const unsigned  &i : atoms)
		_vars.insert(make_pair(i, false));
}

bool Valuation::next()
{
	for(auto b = _vars.rbegin(), e = _vars.rend(); b != e; b++)
	{
		b->second = !b->second;
		if(b->second == true)
			return true;
	}
	return false;
}

void Valuation::print(ostream &ostr) const
{
	for(auto b = _vars.begin(), e = _vars.end(); b != e; b++)
		ostr << b->second << " ";
}

ostream& operator << (ostream &ostr, const Valuation &v)
{
	v.print(ostr);
	return ostr;
}
