#include "Formula.h"

using namespace std;

ostream& operator << (ostream &ostr, const Formula &f)
{
	f->print(ostr);
	return ostr;
}
