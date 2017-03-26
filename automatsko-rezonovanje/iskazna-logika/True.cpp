#include "True.h"

using namespace std;

Type True::getType()
{
	return T_TRUE;
}

void True::print(ostream &ostr)
{
	ostr << "TRUE";
}
