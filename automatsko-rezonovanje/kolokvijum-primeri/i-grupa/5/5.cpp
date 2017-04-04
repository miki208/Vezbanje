/*
5) Napisati C++ program koji omogucava predstavljanje formula u obliku 
   sintaksnog stabla. Formule mogu sadrzati veznike ~, /\, \/, =>. 
   Pretpostaviti da formule ne sadrze logicke konstante. 
   a) implementirati prikaz na izlazu.
   b) implementirati funkciju koja formira kanonsku DNF formu za datu formulu
   F. Kanonska normalna forma se formira na sledeci nacin: posmatraju se sve
   valuacije u kojima je formula tacna (predstavljene kao konjunkcije
   literala koji su tacni u toj valuaciji), a zatim se napravi disjunkcija
   svih takvih konjunkcija. Npr, ako u formuli F imamo 3 varijable p1, p2, i
   p3, i ako su jedine dve valuacije u kojima je F tacna [p1, ~p2, p3], i
   [~p1, ~p2, ~p3], tada je kanonska DNF:
   
   (p1 /\ ~p2 /\ p3)  \/ (~p1 /\ ~p2 /\ ~p3).

   c) Napisati program koji testira ovu funkciju.
*/

#include <memory>
#include <iostream>
#include <map>
#include <vector>
#include <set>

using namespace std;

class BaseFormula;

enum Type {T_ATOM, T_NOT, T_OR, T_AND, T_IMP};
typedef shared_ptr<BaseFormula> Formula;
typedef vector<int> LiteralList;
typedef vector<LiteralList> LiteralListList;
typedef set<unsigned> AtomSet;

ostream& operator << (ostream &ostr, const LiteralListList &ll)
{
	bool f1 = true, f2;
	for(const auto &l : ll) {
		f2 = true;
		if(!f1)
			ostr << " \\/ ";
		f1 = false;

		ostr << "(";
		for(const auto &e : l) {
			if(!f2)
				ostr << " /\\ ";
			f2 = false;

			if(e > 0)
				ostr << "p" << e;
			else
				ostr << "¬p" << (-e);
		}
		ostr << ")";
	}
	return ostr;
}

class Valuation
{
	public:
		Valuation(const AtomSet &as) {
			for(const auto &e : as)
				_m[e] = false;
		}

		bool next() {
			for(auto b = _m.rbegin(), e = _m.rend(); b != e; b++) {
				b->second = !b->second;
				if(b->second == true)
					return true;
			}
			return false;
		}

		const map<unsigned, bool>& getValuation() const {
			return _m;
		}
	private:
		map<unsigned, bool> _m;
};

class BaseFormula : public enable_shared_from_this<BaseFormula>
{
	public:
		virtual void print(ostream&) const = 0;
		virtual Type getType() const = 0;
		virtual void getAtoms(AtomSet&) const = 0;
		virtual bool eval(const Valuation&) const = 0;
		LiteralListList canonical() const {
			LiteralListList res;
			AtomSet as;
			getAtoms(as);
			Valuation val(as);
			do {
				if(eval(val)) {
					LiteralList l;
					const map<unsigned, bool> &m = val.getValuation();
					for(const auto &i : m)
						if(i.second)
							l.push_back(i.first);
						else
							l.push_back(-i.first);
					res.push_back(l);
				}
			} while(val.next());
			return res;
		}
};

ostream& operator << (ostream &ostr, const Formula &f)
{
	f->print(ostr);
	return ostr;
}

class Atom : public BaseFormula
{
	public:
		Atom(unsigned);
		void print(ostream&) const;
		Type getType() const;
		unsigned getId() const;

		void getAtoms(AtomSet &as) const {
			as.insert(_id);
		}

		bool eval(const Valuation &v) const {
			return (v.getValuation().find(_id))->second;
		}
	private:
		unsigned _id;
};

Atom::Atom(unsigned id) : _id(id) { }

void Atom::print(ostream &ostr) const
{
	ostr << "p" << _id;
}

Type Atom::getType() const
{
	return T_ATOM;
}

unsigned Atom::getId() const
{
	return _id;
}

class Not : public BaseFormula
{
	public:
		Not(const Formula&);
		void print(ostream&) const;
		Type getType() const;
		const Formula& getOp() const;

		void getAtoms(AtomSet &as) const {
			_op->getAtoms(as);
		}

		bool eval(const Valuation &v) const {
			return !_op->eval(v);
		}
	private:
		Formula _op;
};

Not::Not(const Formula &f) : _op(f) { }

void Not::print(ostream &ostr) const
{
	ostr << "(¬" << _op << ")";
}

Type Not::getType() const
{
	return T_NOT;
}

const Formula& Not::getOp() const
{
	return _op;
}

class And : public BaseFormula
{
	public:
		And(const Formula&, const Formula&);
		void print(ostream&) const;
		Type getType() const;
		const Formula& getOp1() const;
		const Formula& getOp2() const;

		void getAtoms(AtomSet &as) const {
			_op1->getAtoms(as);
			_op2->getAtoms(as);
		}

		bool eval(const Valuation &v) const {
			return _op1->eval(v) && _op2->eval(v);
		}
	private:
		Formula _op1, _op2;
};

And::And(const Formula &f1, const Formula &f2) : _op1(f1), _op2(f2) { }

void And::print(ostream &ostr) const
{
	ostr << "(" << _op1 << " /\\ " << _op2  << ")";
}

Type And::getType() const
{
	return T_AND;
}

const Formula& And::getOp1() const
{
	return _op1;
}

const Formula& And::getOp2() const
{
	return _op2;
}

class Or : public BaseFormula
{
	public:
		Or(const Formula&, const Formula&);
		void print(ostream&) const;
		Type getType() const;
		const Formula& getOp1() const;
		const Formula& getOp2() const;

		void getAtoms(AtomSet &as) const {
			_op1->getAtoms(as);
			_op2->getAtoms(as);
		}

		bool eval(const Valuation &v) const {
			return _op1->eval(v) || _op2->eval(v);
		}
	private:
		Formula _op1, _op2;
};

Or::Or(const Formula &f1, const Formula &f2) : _op1(f1), _op2(f2) { }

void Or::print(ostream &ostr) const
{
	ostr << "(" << _op1 << " \\/ " << _op2  << ")";
}

Type Or::getType() const
{
	return T_OR;
}

const Formula& Or::getOp1() const
{
	return _op1;
}

const Formula& Or::getOp2() const
{
	return _op2;
}

class Imp : public BaseFormula
{
	public:
		Imp(const Formula&, const Formula&);
		void print(ostream&) const;
		Type getType() const;
		const Formula& getOp1() const;
		const Formula& getOp2() const;

		void getAtoms(AtomSet &as) const {
			_op1->getAtoms(as);
			_op2->getAtoms(as);
		}

		bool eval(const Valuation &v) const {
			return !_op1->eval(v) || _op2->eval(v);
		}
	private:
		Formula _op1, _op2;
};

Imp::Imp(const Formula &f1, const Formula &f2) : _op1(f1), _op2(f2) { }

void Imp::print(ostream &ostr) const
{
	ostr << "(" << _op1 << " => " << _op2  << ")";
}

Type Imp::getType() const
{
	return T_IMP;
}

const Formula& Imp::getOp1() const
{
	return _op1;
}

const Formula& Imp::getOp2() const
{
	return _op2;
}

int main()
{
	Formula p1 = make_shared<Atom>(1);
	Formula p2 = make_shared<Atom>(2);
	Formula p3 = make_shared<Atom>(3);
	Formula and1 = make_shared<And>(p1, p2);
	Formula imp1 = make_shared<Imp>(and1, p3);

	cout << "Formula imp1: " << imp1 << endl;
	cout << "Kanonicka DNF verzija formule imp1: " << imp1->canonical() << endl;

	return 0;
}
