#include "True.h"
#include "False.h"
#include "Atom.h"

using namespace std;

int main()
{
	Formula a = make_shared<True>();
	Formula b = make_shared<False>();
	Formula c = make_shared<Atom>(1);
	
	cout << c << endl;
	cout << c->issat() << endl;	
	return 0;
}
