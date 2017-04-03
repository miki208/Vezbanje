/*
2) Napisati program koji omogucava predstavljanje iskaznih formula u NNF-u.
   Pretpostaviti da konjunkcije i disjunkcije mogu biti n-arne. 
   
   a) Implementirati printFormula()
   b) Implementirati uopstenu zamenu A[l1-->F1, l2-->F2,...,ln-->Fn], gde  se svaki literal li zamenjuje NNF formulom Fi.
   c) Napisati funkciju koja proverava da li je data formula u CNF-u.
   d) Napisati program koji testira funkcije pod a, b, c.
*/

#include <vector>
#include <memory>
#include <iostream>
#include <map>

using namespace std;

//trebace nam konjunkcija, disjunkcija i literali (literale mozemo posmatrati kao atomicne elemente u NNF)

class BaseFormula;

typedef shared_ptr<BaseFormula> Formula;

enum Type { T_AND, T_OR, T_LITERAL };

class BaseFormula : public enable_shared_from_this<BaseFormula>
{
	public:
		virtual void printFormula(ostream&) = 0;
		virtual Type getType() const = 0;
		virtual Formula substitute(const map<int, Formula>&) = 0;
		bool isCnf() const;
	private:
		bool _isCnf(bool) const;
};

ostream& operator << (ostream &ostr, const Formula &f)
{
	f->printFormula(ostr);
	return ostr;
}

class And : public BaseFormula
{
	public:
		And(const vector<Formula>&);
		void printFormula(ostream&);
		Type getType() const;
		Formula substitute(const map<int, Formula>&);
		const vector<Formula>& getOps() const;
	private:
		vector<Formula> _ops;
};

And::And(const vector<Formula> &ops) : _ops(ops) { }

const vector<Formula>& And::getOps() const
{
	return _ops;
}

void And::printFormula(ostream &ostr)
{
	ostr << "( ";
	for(auto i = _ops.begin(), b = _ops.begin(), e = _ops.end(); i != e; i++) {
		if(i != b)
			ostr << " /\\ ";
		ostr << *i;
	}
	ostr << " )";
}

Type And::getType() const
{
	return T_AND;
}

Formula And::substitute(const map<int, Formula> &m)
{
	vector<Formula> sub;

	for(auto i = _ops.begin(), e = _ops.end(); i != e; i++)
		sub.push_back((*i)->substitute(m));

	return make_shared<And>(sub);
}

class Or : public BaseFormula
{
	public:
		Or(const vector<Formula>&);
		void printFormula(ostream&);
		Type getType() const;
		Formula substitute(const map<int, Formula>&);
		const vector<Formula>& getOps() const;
	private:
		vector<Formula> _ops;
};

Or::Or(const vector<Formula> &ops) : _ops(ops) { }

const vector<Formula>& Or::getOps() const
{
	return _ops;
}

void Or::printFormula(ostream &ostr)
{
	ostr << "( ";
	for(auto b = _ops.begin(), i = _ops.begin(), e = _ops.end(); i != e; i++) {
		if(i != b)
			ostr << " \\/ ";
		ostr << *i;
	}
	ostr << " )";
}

Type Or::getType() const
{
	return T_OR;
}

Formula Or::substitute(const map<int, Formula> &m)
{
	vector<Formula> sub;

	for(auto i = _ops.begin(), e = _ops.end(); i != e; i++)
		sub.push_back((*i)->substitute(m));

	return make_shared<Or>(sub);
}

class Literal : public BaseFormula
{
	public:
		Literal(int);
		void printFormula(ostream&);
		Type getType() const;
		Formula substitute(const map<int, Formula>&);
	private:
		int _id;//negativni su za suprotni literal 
};

Literal::Literal(int id) : _id(id) { }

void Literal::printFormula(ostream &ostr)
{
	if(_id < 0)
		ostr << "¬p" << (-_id);
	else
		ostr << "p" << _id;
}

Type Literal::getType() const
{
	return T_LITERAL;
}

Formula Literal::substitute(const map<int, Formula> &m)
{
	const auto &f = m.find(_id);

	if(f == m.end())
		return shared_from_this();
	return f->second;
}

//ideja je da se posle prve pojave disjunkcije u stablu vise ne pojavi nijedna konjunkcija
bool BaseFormula::isCnf() const
{
	return _isCnf(false);//prvi parametar govori da li se pojavila disjunkcija
}

bool BaseFormula::_isCnf(bool disj) const
{
	if(getType() == T_LITERAL)
		return true;
	else if(getType() == T_OR) {
		for(auto i = ((Or*) this)->getOps().begin(), e = ((Or*) this)->getOps().end(); i != e; i++) {
			bool rez = (*i)->_isCnf(true);
			if(rez == false)
				return false;
		}
		return true;
	} else { //T_AND
		if(disj)
			return false;
		for(auto i = ((And*) this)->getOps().begin(), e = ((And*) this)->getOps().end(); i != e; i++) {
			bool rez = (*i)->_isCnf(disj);
			if(rez == false)
				return false;
		}
		return true;
	}
}

int main()
{
	Formula p1 = make_shared<Literal>(1);
	Formula p2 = make_shared<Literal>(2);
	Formula np1 = make_shared<Literal>(-1);
	Formula and1 = make_shared<And>(initializer_list<Formula>{p1, p2});
	Formula or1 = make_shared<Or>(initializer_list<Formula>{np1, and1});
	Formula or2 = make_shared<Or>(initializer_list<Formula>{np1, p2});

	cout << or1 << endl;
	cout << or1->substitute(map<int, Formula>{make_pair(-1, and1)}) << endl;
	cout << or1->isCnf() << endl;

	Formula cnf = make_shared<And>(initializer_list<Formula>{or2, p1});
	cout << cnf << endl;
	cout << or2->isCnf() << endl;
	return 0;
}
