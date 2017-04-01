/*
1) Napisati C++ program koji omogucava predstavljanje iskaznih formula koje
   ukljucuju veznike ~, /\, \/, u obliku sintaksnog stabla. Pretpostaviti da
   su konjunkcije i disjunkcije n-arne, tj. da se svaka od njih primenjuje
   na dve ili vise podformule. 

   a) Implementirati virtuelnu funkciju clanicu printFormula() za 
   prikazivanje formule na standardnom izlazu u uobicajenoj konkretnoj 
   sintaksi. 
   b) Napisati funkciju koja za datu CNF formulu predstavljenu u obliku
   liste listi (sto smo radili na casu) formira sintaksno stablo.
   c) Napisati program koji poziva funkciju pod b),a zatim prikazuje formulu
   pomocu funkcije iz dela pod a).
*/

#include <vector>
#include <memory>
#include <iostream>

using namespace std;

class BaseFormula;
typedef shared_ptr<BaseFormula> Formula;
enum Type {T_AND, T_OR, T_NOT, T_ATOM, T_TRUE, T_FALSE};
typedef vector<Formula> LiteralList;
typedef vector<LiteralList> LiteralListList;

class BaseFormula : public enable_shared_from_this<BaseFormula>
{
	public:
	virtual void printFormula(ostream&) const = 0;
	virtual Type getType() const = 0;
};

ostream& operator << (ostream &ostr, const Formula &f)
{
	f->printFormula(ostr);
	return ostr;
}

class True : public BaseFormula
{
	public:
		void printFormula(ostream&) const;
		Type getType() const;
};

void True::printFormula(ostream &ostr) const
{
	ostr << "TRUE";
}

Type True::getType() const
{
	return T_TRUE;
}

class False : public BaseFormula
{
	public:
		void printFormula(ostream&) const;
		Type getType() const;
};

void False::printFormula(ostream &ostr) const
{
	ostr << "FALSE";
}

Type False::getType() const
{
	return T_FALSE;
}

class Atom : public BaseFormula
{
	public:
		Atom(unsigned);
		void printFormula(ostream&) const;
		Type getType() const;

	private:
		unsigned _id;
};

Atom::Atom(unsigned id) : _id(id) { }

void Atom::printFormula(ostream &ostr) const
{
	ostr << "p" << _id;
}

Type Atom::getType() const
{
	return T_ATOM;
}

class Not : public BaseFormula
{
	public:
		Not(const Formula&);
		void printFormula(ostream&) const;
		Type getType() const;

	private:
		Formula _op;
};

Not::Not(const Formula &f) : _op(f) {}

void Not::printFormula(ostream &ostr) const
{
	ostr << "¬" << _op;
}

Type Not::getType() const
{
	return T_NOT;
}

class And : public BaseFormula
{
	public:
		And(const vector<Formula>&);
		void printFormula(ostream&) const;
		Type getType() const;

	private:
		vector<Formula> _ops;
};

And::And(const vector<Formula> &ops) : _ops(ops) {}

void And::printFormula(ostream &ostr) const
{
	ostr << "( ";
	for(auto i = _ops.begin(), first = _ops.begin(), j = _ops.end(); i != j; i++) {
		if(i != first)
			ostr << " /\\ ";
		ostr << *i;
	}
	ostr << " )";
}

Type And::getType() const
{
	return T_AND;
}

class Or : public BaseFormula
{
	public:
		Or(const vector<Formula>&);
		void printFormula(ostream&) const;
		Type getType() const;

	private:
		vector<Formula> _ops;
};

Or::Or(const vector<Formula> &ops) : _ops(ops) {}

void Or::printFormula(ostream &ostr) const
{
	ostr << "( ";
	for(auto i = _ops.begin(), first = _ops.begin(), j = _ops.end(); i != j; i++) {
		if(i != first)
			ostr << " \\/ ";
		ostr << *i;
	}
	ostr << " )";
}

Type Or::getType() const
{
	return T_OR;
}

Formula LiteralListListToFormula(const LiteralListList &ll)
{
	vector<Formula> andOps;
	for(auto& l : ll)
		andOps.push_back(make_shared<Or>(l));
	return make_shared<And>(andOps);
}

int main()
{
	Formula p1 = make_shared<Atom>(1);
	Formula p2 = make_shared<Atom>(2);
	Formula p3 = make_shared<Atom>(3);

	LiteralListList ll = { {p1, make_shared<Not>(p2)}, {make_shared<Not>(p1), p2}, {p3} };
	cout << LiteralListListToFormula(ll) << endl;
	return 0;
}
