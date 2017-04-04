/*
4) Napisati program koji omogucava predstavljanje formula koje ukljucuju 
   unarni veznik ~, kao i binarne veznike \/, /\, =>. 

   a) Definisati uopstenu zamenu A[p1-->F1, p2-->F2,...,pn-->Fn], gde se
   iskazna varijabla pi zamenjuje formulom Fi.
   b) Definisati proceduru koja ispituje da li je jedna formula instanca
   druge. Formula G je instanca formule F, ako postoji uopstena zamena
   takva da je G = F[p1-->F1,...,pn->Fn].
   c) Napisati program koji testira gornje funkcije.
*/

#include <memory>
#include <iostream>
#include <map>

using namespace std;

class BaseFormula;

enum Type {T_ATOM, T_TRUE, T_FALSE, T_NOT, T_OR, T_AND, T_IMP}; //moguce je da TRUE i FALSE nisu neophodni
typedef shared_ptr<BaseFormula> Formula;

class BaseFormula : public enable_shared_from_this<BaseFormula>
{
	public:
		virtual void print(ostream&) const = 0;
		virtual Type getType() const = 0;
		virtual Formula substitute(const map<unsigned, Formula>&) = 0;
		bool isInstanceOf(const Formula&, map<unsigned, Formula>&);
};

ostream& operator << (ostream &ostr, const Formula &f)
{
	f->print(ostr);
	return ostr;
}

class True : public BaseFormula
{
	public:
		void print(ostream&) const;
		Type getType() const;
		Formula substitute(const map<unsigned, Formula>&);
};

void True::print(ostream &ostr) const
{
	ostr << "TRUE";
}

Type True::getType() const
{
	return T_TRUE;
}

Formula True::substitute(const map<unsigned, Formula> &m)
{
	return shared_from_this();
}

class False : public BaseFormula
{
	public:
		void print(ostream&) const;
		Type getType() const;
		Formula substitute(const map<unsigned, Formula>&);
};

void False::print(ostream &ostr) const
{
	ostr << "FALSE";
}

Type False::getType() const
{
	return T_FALSE;
}

Formula False::substitute(const map<unsigned, Formula> &m)
{
	return shared_from_this();
}

class Atom : public BaseFormula
{
	public:
		Atom(unsigned);
		void print(ostream&) const;
		Type getType() const;
		Formula substitute(const map<unsigned, Formula>&);
		unsigned getId() const;
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

Formula Atom::substitute(const map<unsigned, Formula> &m)
{
	const auto i = m.find(_id);
	if(i != m.end())
		return i->second;
	return shared_from_this();
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
		Formula substitute(const map<unsigned, Formula>&);
		const Formula& getOp() const;
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

Formula Not::substitute(const map<unsigned, Formula> &m)
{
	Formula sub = _op->substitute(m);
	return make_shared<Not>(sub);
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
		Formula substitute(const map<unsigned, Formula>&);
		const Formula& getOp1() const;
		const Formula& getOp2() const;
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

Formula And::substitute(const map<unsigned, Formula> &m)
{
	Formula sub1 = _op1->substitute(m);
	Formula sub2 = _op2->substitute(m);
	return make_shared<And>(sub1, sub2);
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
		Formula substitute(const map<unsigned, Formula>&);
		const Formula& getOp1() const;
		const Formula& getOp2() const;
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

Formula Or::substitute(const map<unsigned, Formula> &m)
{
	Formula sub1 = _op1->substitute(m);
	Formula sub2 = _op2->substitute(m);
	return make_shared<Or>(sub1, sub2);
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
		Formula substitute(const map<unsigned, Formula>&);
		const Formula& getOp1() const;
		const Formula& getOp2() const;
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

Formula Imp::substitute(const map<unsigned, Formula> &m)
{
	Formula sub1 = _op1->substitute(m);
	Formula sub2 = _op2->substitute(m);
	return make_shared<Imp>(sub1, sub2);
}

const Formula& Imp::getOp1() const
{
	return _op1;
}

const Formula& Imp::getOp2() const
{
	return _op2;
}

bool BaseFormula::isInstanceOf(const Formula &f, map<unsigned, Formula> &m)
{
	if(f->getType() == T_ATOM) {
		m[((Atom*) f.get())->getId()] = shared_from_this();
		return true;
	} else if(f->getType() != getType()) {
		return false;
	} else {
		if(getType() == T_NOT) {
			return ((Not*) this)->getOp()->isInstanceOf(((Not*)f.get())->getOp(), m);
		} else if(getType() == T_AND) {
			return ((And*) this)->getOp1()->isInstanceOf(((And*)f.get())->getOp1(), m) &&
				((And*) this)->getOp2()->isInstanceOf(((And*)f.get())->getOp2(), m);
		} else if(getType() == T_OR) {
			return ((Or*) this)->getOp1()->isInstanceOf(((Or*)f.get())->getOp1(), m) &&
				((Or*) this)->getOp2()->isInstanceOf(((Or*)f.get())->getOp2(), m);
		} else { //T_IMP
			return ((Imp*) this)->getOp1()->isInstanceOf(((Imp*)f.get())->getOp1(), m) &&
				((Imp*) this)->getOp2()->isInstanceOf(((Imp*)f.get())->getOp2(), m);
		}
	}
}

int main()
{
	Formula p1 = make_shared<Atom>(1);
	Formula p2 = make_shared<Atom>(2);
	Formula or1 = make_shared<Or>(p1, p2);
	Formula p3 = make_shared<Atom>(3);
	Formula p4 = make_shared<Atom>(4);
	Formula imp1 = make_shared<Imp>(p3, p4);
	Formula and1 = make_shared<And>(or1, imp1);

	cout << "Formula and1: " << and1 << endl;

	Formula sub = and1->substitute(map<unsigned, Formula>{make_pair(1, or1), make_pair(2, imp1)});

	cout << "Supstitucija and1[p1 -> (p1 \\/ p2), p2 -> (p3 -> p4)] = " << sub << endl;

	map<unsigned, Formula> s;
	if(sub->isInstanceOf(and1, s)) {
		cout << "sub je instanca formule and1, supstitucija je: " << endl;
		for(auto &elem : s)
			cout << "\tp" << elem.first << " -> " << elem.second << endl;
	} else {
		cout << "sub nije instanca formule and1" << endl;
	}

	s.clear();
	if(and1->isInstanceOf(sub, s))
		cout << "and1 je instanca formule sub" << endl;
	else
		cout << "and1 nije instanca formule sub" << endl;

	return 0;
}
