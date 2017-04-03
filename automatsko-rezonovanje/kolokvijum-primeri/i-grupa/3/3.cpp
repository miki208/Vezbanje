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
	bool find = false;
	for(auto &i : a) {
		if(b.find(-i) != b.end()) {
			if(find == false) {
				find = true;
				for(auto &j : a) {
					if(j != i)
						res.insert(j);
				}

				for(auto &j : b) {
					if(j != -i)
						res.insert(j);
				}
			} else {
				res.erase(i);
				res.erase(-i);
			}
		}
	}
	return find;
}

bool resolution(Formula f)//vraca true ako je izvedena prazna klauza
{
	Clause tmp;
	for(int i = 1; i < f.size(); i++) {
		for(int j = i - 1; j >= 0; j--) {
			if(resolve(f[i], f[j], tmp)) {
				if(tmp.empty())
					return true;
				f.push_back(tmp);
			}
		}
	}
	return false;
}

int main()
{
	Formula f = { {1, 2, 3}, {-1, -2}, {-2, -3}, {-1, -3} };
	Clause res;
	cout << f << endl;
	
	if(resolve(f[0], f[1], res))
		cout << res << endl;

	cout << resolution(f) << endl;
	return 0;
}
