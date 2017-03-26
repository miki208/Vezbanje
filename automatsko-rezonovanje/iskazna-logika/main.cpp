#include "True.h"
#include "False.h"
#include "Atom.h"
#include "And.h"
#include "Or.h"
#include "Iff.h"
#include "Imp.h"
#include "Not.h"

using namespace std;

int main()
{
	Formula p1 = make_shared<Atom>(1);
	Formula p2 = make_shared<Atom>(2);
	Formula p3 = make_shared<Atom>(3);
	Formula p4 = make_shared<Atom>(4);
	Formula np2 = make_shared<Not>(p2);
	Formula np3 = make_shared<Not>(p3);
	Formula np4 = make_shared<Not>(p4);
	Formula imp1 = make_shared<Imp>(p1, np2);
	Formula and1 = make_shared<And>(p3, np4);
	Formula or1 = make_shared<Or>(imp1, and1);
	Formula imp2 = make_shared<Imp>(np3, p2);
	Formula iff1 = make_shared<Iff>(or1, imp2);

	Valuation v;
	cout << iff1 << endl;
	if(iff1->issat(v))
		cout << "Formula je zadovoljiva u valuaciji " << v << endl;
	return 0;
}
