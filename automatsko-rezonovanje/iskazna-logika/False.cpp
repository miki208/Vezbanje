#include "False.h"

using namespace std;

Type False::getType() const
{
	return T_FALSE;
}

void False::print(ostream &ostr) const
{
	ostr << "FALSE";
}

bool False::eval(const Valuation &v) const
{
	return false;
}
