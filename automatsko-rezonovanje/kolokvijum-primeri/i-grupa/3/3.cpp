/*
3) Napisati program koji omogucava predstavljanje formula u CNF-u (u obliku
   liste klauza, gde je klauza lista literala, ili nekako drugacije).

   a) Implementirati prikaz date CNF formule na izlazu.
   b) Implementirati funkciju resolve() koja na dve klauze primenjuje metod
   rezolucije, ukoliko je to moguce, pri cemu proizvodi novu rezolventnu
   klauzu (npr. [-1 2 3], [-2 3 4], moze se primeniti pravilo rezolucije nad
   drugim literalom prve klauze i prvim literalom druge klauze, pri cemu se
   dobija nova klauza [-1 3 4]; obezbediti eliminisanje duplikata iz
   rezolvente).
   c) Pomocu funkcije iz dela pod b), implementirati metod rezolucije, tako
   sto se sistematski primenjuje metod rezolucije dokle god je to moguce,
   sve dok se ne izvede prazna klauza, ili se ne utvrdi da to nije moguce.
   d) Napisati program koji testira funkcije pod a, b, c.
*/

#include <set>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef set<int> Clause;
typedef vector<Clause> Formula;

ostream& operator << (ostream &ostr, Clause c) {
	ostr << " [";
	for(auto &i : c)
		ostr << i << " ";
	ostr << "]";
	return ostr;
}

ostream& operator << (ostream &ostr, Formula f)
{
	ostr << "[";
	for(auto &i : f) {
		ostr << i;
	}
	ostr << " ]";
	return ostr;
}

bool resolve(const Clause &a, const Clause &b, Clause &res)
{
	res.clear();
	for(auto &i : a) {
		if(b.find(-i) != b.end()) {
			for(auto &j : a) {
				if(j != i)
					res.insert(j);
			}
			for(auto &j : b) {
				if(j != -i)
					res.insert(j);
			}
			return true;
		}
	}
	return false;
}

bool resolution(Formula f)//vraca true ako je izvedena kontradikcija
{
	Clause tmp;
	for(int i = 1; i < f.size(); i++) {
		for(int j = i - 1; j >= 0; j--) {
			if(resolve(f[i], f[j], tmp)) {
				if(tmp.empty())
					return true;
				if(find(f.begin(), f.end(), tmp) == f.end())//moramo da proverimo da li je vec izvedena ova rezolventa
					f.push_back(tmp);
			}
		}
	}
	return false;
}

int main()
{
	Formula f = {{-1, -2, 3}, {-1, 2}, {1}, {-3}};
	Clause res;

	cout << "Test formula: " << f << endl;
	
	if(resolve(f[0], f[1], res))
		cout << "Iz prve i druge klauze je izvedena rezolventa " << res << endl;


	if(resolution(f))
		cout << "Izvedena je prazna klauza, formula f je nezadovoljiva" << endl;
	else
		cout << "Nije izvedena prazna klauza, formula f je zadovoljiva" << endl;
	return 0;
}
