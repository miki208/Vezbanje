#include "True.h"

using namespace std;

int main()
{
	Formula a = make_shared<True>();
	Formula b = make_shared<True>();
		cout << a << " | complexity: " << a->complexity() << endl;
		if(a->equalsTo(b)) {
		cout << "A i B su jednake formule." << endl;
	}

	AtomSet atoms;
	a->getAtoms(atoms);
	Valuation v;
	v.init(atoms);
	cout << a->eval(v) << endl;
	return 0;
}
