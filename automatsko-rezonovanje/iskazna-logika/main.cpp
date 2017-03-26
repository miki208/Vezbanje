#include "True.h"
#include "False.h"
#include "Atom.h"
#include "And.h"

using namespace std;

int main()
{
	Formula a = make_shared<True>();
	Formula b = make_shared<False>();
	Formula c = make_shared<Atom>(1);
	Formula d = make_shared<And>(a, b);

	cout << d << endl;
	cout << d->issat() << endl;	
	return 0;
}
