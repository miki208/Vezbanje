#include "True.h"

using namespace std;

Type True::getType() const
{
	return T_TRUE;
}

void True::print(ostream &ostr) const
{
	ostr << "TRUE";
}

bool True::eval(const Valuation &v) const
{
	return true;
}
