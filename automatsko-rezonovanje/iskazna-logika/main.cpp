#include "True.h"
#include "False.h"
#include "Atom.h"
#include "And.h"
#include "Or.h"

using namespace std;

int main()
{
	Formula a = make_shared<True>();
	Formula b = make_shared<False>();
	Formula c = make_shared<Atom>(1);
	Formula d = make_shared<Atom>(2);
	Formula e = make_shared<And>(c, d);
	Formula f = make_shared<Atom>(3);
	Formula g = make_shared<Or>(e, f);

	Valuation v;
	cout << g << endl;
	if(g->issat(v))
		cout << "Formula je zadovoljiva u valuaciji " << v << endl;
	return 0;
}
