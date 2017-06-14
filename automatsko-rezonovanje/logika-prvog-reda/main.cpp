#include <memory>
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

class BaseTerm;
class BaseFormula;

typedef string FunctionSymbol;
typedef string PredicateSymbol;
typedef string Variable;
typedef set<Variable> VariableSet;
typedef shared_ptr<BaseTerm> Term;
typedef shared_ptr<BaseFormula> Formula;
typedef vector<unsigned> Domain;

/*
- Implementirati klasu Signature
	- Dodavanje funkcijskog simbola
	- Dodavanje predikatskog simbola
	- Provera funkcijskog simbola
	- Provera predikatskog simbola
*/

class Signature
{
	public:
		void addFunctionSymbol(const FunctionSymbol &f, unsigned arity);
		void addPredicateSymbol(const PredicateSymbol &p, unsigned arity);
		bool checkFunctionSymbol(const FunctionSymbol &f, unsigned &arity) const;
		bool checkPredicateSymbol(const PredicateSymbol &p, unsigned &arity) const;

	private:
		map<FunctionSymbol, unsigned> _functions;
		map<PredicateSymbol, unsigned> _predicates;
};

/*
- Apstrakcija interpretacije funkcije
	- Arnost
	- Evaluacija

*/

class Function
{
	public:
		Function(unsigned arity);
		unsigned getArity() const;
		virtual unsigned eval(const vector<unsigned> &args = vector<unsigned>()) const = 0;

	private:
		unsigned _arity;
};

/*
- Apstrakcija interpretacije relacije
	- Arnost
	- Evaluacija
*/

class Relation
{
	public:
		Relation(unsigned arity);
		unsigned getArity() const;
		virtual bool eval(const vector<unsigned> &args = vector<unsigned>()) const = 0;

	private:
		unsigned _arity;
};

/*
- Struktura (model)
	- Vracanje signature
	- Vracanje domena
	- Dodavanje interpretacije funkcije
	- Vracanje funkcije
	- Dodavanje interpretacije relacije
	- Vracanje relacije
*/

class Structure
{
	public:
		Structure(const Signature &sig, const Domain &dom);
		~Structure();

		const Domain& getDomain() const;
		const Signature& getSignature() const;
		void addFunction(const FunctionSymbol &fs, Function *f);
		void addRelation(const PredicateSymbol &ps, Relation *r);
		Function* getFunction(const FunctionSymbol &fs) const;
		Relation* getRelation(const PredicateSymbol &ps) const;

	private:
		Signature _sig;
		Domain _dom;
		map<FunctionSymbol, Function*> _funs;
		map<PredicateSymbol, Relation*> _rels;
};

/*
- Apstrakcija valuacije
	- Vracanje domena
	- Postavljanje vrednosti
	- Vracanje vrednosti
*/

class Valuation
{
	public:
		Valuation(const Domain &dom);

		const Domain& getDomain() const;
		void setValue(const Variable &v, unsigned val);
		unsigned getValue(const Variable &v) const;

		friend ostream& operator<<(ostream&, const Valuation&);
	private:
		const Domain &_dom;
		map<Variable, unsigned> _values;
};

ostream& operator<<(ostream &ostr, const Valuation &v)
{
	ostr << "{\n";

	for(const auto &i : v._values)
		ostr << "\t" << i.first << " : " << i.second << "\n";

	ostr << "}";

	return ostr;
}

/*
- Implementirati termove (promenljiva, funkcija)
	- Provera tipa
	- Ispis terma
	- Sintaksna jednakost
	- Vracanje svih promenljivih
	- Provera da li sadrzi odredjenu promenljivu
	- Evaluacija
	- Supstitucija promenljive sa termom
*/

class BaseTerm : public enable_shared_from_this<BaseTerm>
{
	public:
		enum Type { TT_VARIABLE, TT_FUNCTION };

		virtual Type getType() const = 0;
		virtual void print(ostream &ostr) const = 0;
		virtual bool equalTo(const Term &t) const = 0;
		virtual void getVars(VariableSet &vs) const = 0;
		bool containsVar(const Variable &v) const;
		virtual unsigned eval(const Structure &s, const Valuation &v) const = 0;
		virtual Term substitute(const Variable &v, const Term &t) = 0;
};

ostream& operator<<(ostream &ostr, const Term &t)
{
	t->print(ostr);

	return ostr;
}

/*
- Funkcijski termovi
	- Vracanje operanada
	- Vracanje signature
	- Vracanje funkcijskog simbola
*/

class FunctionTerm : public BaseTerm
{
	public:
		FunctionTerm(const Signature &sig, const FunctionSymbol &f, const vector<Term> &ops);
		FunctionTerm(const Signature &sig, const FunctionSymbol &f, vector<Term> &&ops = vector<Term>());

		Type getType() const;
		void print(ostream &ostr) const;
		bool equalTo(const Term &t) const;
		void getVars(VariableSet &vs) const;
		unsigned eval(const Structure &s, const Valuation &v) const;
		Term substitute(const Variable &v, const Term &t);

		const Signature& getSignature() const;
		const vector<Term>& getOperands() const;
		const FunctionSymbol& getSymbol() const;

	private:
		vector<Term> _ops;
		FunctionSymbol _f;
		Signature _sig;
};

class VariableTerm : public BaseTerm
{
	public:
		VariableTerm(const Variable &v);
		
		Type getType() const;
		void print(ostream &ostr) const;
		bool equalTo(const Term &t) const;
		void getVars(VariableSet &vs) const;
		unsigned eval(const Structure &s, const Valuation &v) const;
		Term substitute(const Variable &v, const Term &t);

		const Variable& getVariable() const;
	private:
		Variable _v;
};

/*
- Implementirati formule
	- Ispis formule
	- Tip formule
	- Kompleksnost
	- Sintaksna jednakost
	- Vracanje svih (slobodnih) promenljivih
	- Provera da li sadrzi odredjenu vezanu ili slobodnu promenljivu
	- Evaluacija
	- Supstitucija promenljive sa termom
*/

class BaseFormula : public enable_shared_from_this<BaseFormula>
{
	public:
		enum Type {T_TRUE, T_FALSE, T_ATOM, T_NOT, T_AND, T_OR, T_IMP, T_IFF, T_FORALL, T_EXISTS};

		virtual void print(ostream &ostr) const = 0;
		virtual Type getType() const = 0;
		virtual unsigned complexity() const = 0;
		virtual bool equalTo(const Formula &f) const = 0;
		virtual void getVars(VariableSet &vs, bool free = false) const = 0;
		bool containsVar(const Variable &v, bool free = false) const;
		virtual bool eval(const Structure &st, const Valuation &v) const = 0;
		virtual Formula substitute(const Variable &v, const Term &t) = 0;
};

ostream& operator<<(ostream &ostr, const Formula &f)
{
	f->print(ostr);
	
	return ostr;
}

Variable getUniqueVariable(const Formula &f, const Term &t);

class AtomicFormula : public BaseFormula
{
	public:
		unsigned complexity() const;
};

class LogicConstant : public AtomicFormula
{
	public:
		bool equalTo(const Formula &f) const;
		void getVars(VariableSet &vs, bool free) const;
		Formula substitute(const Variable &v, const Term &t);
};

class True : public LogicConstant
{
	public:
		void print(ostream &ostr) const;
		Type getType() const;
		bool eval(const Structure &st, const Valuation &v) const;
};

class False : public LogicConstant
{
	public:
		void print(ostream &ostr) const;
		Type getType() const;
		bool eval(const Structure &st, const Valuation &v) const;
};

class Atom : public AtomicFormula
{
	public:
		Atom(const Signature &sig, const PredicateSymbol &p, const vector<Term> &ops);
		Atom(const Signature &sig, const PredicateSymbol &p, vector<Term> &&ops = vector<Term>());

		const PredicateSymbol& getSymbol() const;
		const Signature& getSignature() const;
		const vector<Term>& getOperands() const;

		void print(ostream &ostr) const;
		Type getType() const;
		bool eval(const Structure &st, const Valuation &v) const;
		bool equalTo(const Formula &f) const;
		void getVars(VariableSet &vs, bool free) const;
		Formula substitute(const Variable &v, const Term &t);

	private:
		PredicateSymbol _p;
		Signature _sig;
		vector<Term> _ops;
};

class UnaryConnective : public BaseFormula
{
	public:
		UnaryConnective(const Formula &op);

		const Formula& getOperand() const;
		unsigned complexity() const;
		bool equalTo(const Formula &f) const;
		void getVars(VariableSet &vs, bool free = false) const;

	protected:
		Formula _op;
};

class Not : public UnaryConnective
{
	public:
		using UnaryConnective::UnaryConnective;

		void print(ostream &ostr) const;
		Type getType() const;
		bool eval(const Structure &st, const Valuation &v) const;
		Formula substitute(const Variable &v, const Term &t);
};

class BinaryConnective : public BaseFormula
{
	public:
		BinaryConnective(const Formula &op1, const Formula &_op2);

		const Formula& getOperand1() const;
		const Formula& getOperand2() const;
		unsigned complexity() const;
		bool equalTo(const Formula &f) const;
		void getVars(VariableSet &vs, bool free = false) const;

	protected:
		Formula _op1;
		Formula _op2;
};

class And : public BinaryConnective
{
	public:
		using BinaryConnective::BinaryConnective;

		void print(ostream &ostr) const;
		Type getType() const;
		bool eval(const Structure &st, const Valuation &v) const;
		Formula substitute(const Variable &v, const Term &t);
};

class Or : public BinaryConnective
{
	public:
		using BinaryConnective::BinaryConnective;

		void print(ostream &ostr) const;
		Type getType() const;
		bool eval(const Structure &st, const Valuation &v) const;
		Formula substitute(const Variable &v, const Term &t);
};

class Imp : public BinaryConnective
{
	public:
		using BinaryConnective::BinaryConnective;

		void print(ostream &ostr) const;
		Type getType() const;
		bool eval(const Structure &st, const Valuation &v) const;
		Formula substitute(const Variable &v, const Term &t);
};

class Iff : public BinaryConnective
{
	public:
		using BinaryConnective::BinaryConnective;

		void print(ostream &ostr) const;
		Type getType() const;
		bool eval(const Structure &st, const Valuation &v) const;
		Formula substitute(const Variable &v, const Term &t);
};

class Quantifier : public BaseFormula
{
	public:
		Quantifier(const Variable &v, const Formula &f);
		const Variable& getVariable() const;
		const Formula& getOperand() const;
		unsigned complexity() const;
		bool equalTo(const Formula &f) const;
		void getVars(VariableSet &vs, bool free = false) const;

	protected:
		Variable _v;
		Formula _op;
};

class Forall : public Quantifier
{
	public:
		using Quantifier::Quantifier;

		void print(ostream &ostr) const;
		Type getType() const;
		bool eval(const Structure &st, const Valuation &v) const;
		Formula substitute(const Variable &v, const Term &t);
};

class Exists : public Quantifier
{
	public:
		using Quantifier::Quantifier;

		void print(ostream &ostr) const;
		Type getType() const;
		bool eval(const Structure &st, const Valuation &v) const;
		Formula substitute(const Variable &v, const Term &t);
};

/* class Signature */
void Signature::addFunctionSymbol(const FunctionSymbol &f, unsigned arity)
{
	_functions.insert(make_pair(f, arity));
}

void Signature::addPredicateSymbol(const PredicateSymbol &p, unsigned arity)
{
	_predicates.insert(make_pair(p, arity));
}

bool Signature::checkFunctionSymbol(const FunctionSymbol &f, unsigned &arity) const
{
	auto it = _functions.find(f);
	if(it != _functions.cend()) {
			arity = it->second;
			return true;
	}

	return false;
}

bool Signature::checkPredicateSymbol(const PredicateSymbol &p, unsigned &arity) const
{
	auto it = _predicates.find(p);
	if(it != _predicates.cend()) {
		arity = it->second;
		return true;
	}

	return false;
}

/* class BaseTerm */
bool BaseTerm::containsVar(const Variable &v) const
{
	VariableSet vs;
	getVars(vs);

	return vs.find(v) != vs.end();
}

/* class FunctionTerm */
FunctionTerm::FunctionTerm(const Signature &sig, const FunctionSymbol &f, const vector<Term> &ops) : _ops(ops), _sig(sig), _f(f)
{
	unsigned ar;
	if(!sig.checkFunctionSymbol(f, ar) || ar != _ops.size())
		throw "Syntax error!";
}

FunctionTerm::FunctionTerm(const Signature &sig, const FunctionSymbol &f, vector<Term> &&ops) : _ops(move(ops)), _sig(sig), _f(f)
{
	unsigned ar;
	if(!sig.checkFunctionSymbol(f, ar) || ar != _ops.size())
		throw "Syntax error!";
}

BaseTerm::Type FunctionTerm::getType() const
{
	return TT_FUNCTION;
}

void FunctionTerm::print(ostream &ostr) const
{
	ostr << _f;
	for(int i = 0; i < _ops.size(); i++) {
		if(i == 0)
			ostr << "(";
		else
			ostr << ", ";

		ostr << _ops[i];
	}
	if(_ops.size() > 0)
		ostr << ")";
}

bool FunctionTerm::equalTo(const Term &t) const
{
	if(t->getType() != TT_FUNCTION || _f != ((FunctionTerm*) t.get())->getSymbol())
		return false;

	const vector<Term> &ops = ((FunctionTerm*) t.get())->getOperands();
	if(ops.size() != _ops.size())
		return false;

	for(int i = 0; i < ops.size(); i++)
		if(!_ops[i]->equalTo(ops[i]))
			return false;

	return true;
}

void FunctionTerm::getVars(VariableSet &vs) const
{
	for(int i = 0; i < _ops.size(); i++)
		_ops[i]->getVars(vs);
}

unsigned FunctionTerm::eval(const Structure &s, const Valuation &v) const
{
	Function *f = s.getFunction(_f);

	vector<unsigned> args;
	for(int i = 0; i < _ops.size(); i++)
		args.push_back(_ops[i]->eval(s, v));

	return f->eval(args);
}

Term FunctionTerm::substitute(const Variable &v, const Term &t)
{
	vector<Term> new_ops;

	for(int i = 0; i < _ops.size(); i++)
		new_ops.push_back(_ops[i]->substitute(v, t));

	return make_shared<FunctionTerm>(_sig, _f, new_ops);
}

const Signature& FunctionTerm::getSignature() const
{
	return _sig;
}

const vector<Term>& FunctionTerm::getOperands() const
{
	return _ops;
}

const FunctionSymbol& FunctionTerm::getSymbol() const
{
	return _f;
}

/* class VariableTerm */
VariableTerm::VariableTerm(const Variable &v) : _v(v)
{

}
		
BaseTerm::Type VariableTerm::getType() const
{
	return TT_VARIABLE;
}

void VariableTerm::print(ostream &ostr) const
{
	ostr << _v;
}

bool VariableTerm::equalTo(const Term &t) const
{
	return t->getType() == TT_VARIABLE &&_v == ((VariableTerm*) t.get())->getVariable();
}

void VariableTerm::getVars(VariableSet &vs) const
{
	vs.insert(_v);
}

unsigned VariableTerm::eval(const Structure &s, const Valuation &v) const
{
	return v.getValue(_v);
}

Term VariableTerm::substitute(const Variable &v, const Term &t)
{
	if(_v == v)
		return t;
	return shared_from_this();
}

const Variable& VariableTerm::getVariable() const
{
	return _v;
}

/* class Function */
Function::Function(unsigned arity) : _arity(arity)
{

}

unsigned Function::getArity() const
{
	return _arity;
}

/* class Relation */

Relation::Relation(unsigned arity) : _arity(arity)
{

}

unsigned Relation::getArity() const
{
	return _arity;
}

/* class Structure */
Structure::Structure(const Signature &sig, const Domain &dom) : _sig(sig), _dom(dom)
{

}

Structure::~Structure()
{
	for(const auto &f : _funs)
		delete f.second;

	for(const auto &p : _rels)
		delete p.second;
}

const Domain& Structure::getDomain() const
{
	return _dom;
}

const Signature& Structure::getSignature() const
{
	return _sig;
}

void Structure::addFunction(const FunctionSymbol &fs, Function *f)
{
	unsigned ar;
	if(!_sig.checkFunctionSymbol(fs, ar) || ar != f->getArity())
		throw "Function arity mismatch!";

	_funs.insert(make_pair(fs, f));
}

void Structure::addRelation(const PredicateSymbol &ps, Relation *r)
{
	unsigned ar;
	if(!_sig.checkPredicateSymbol(ps, ar) || ar != r->getArity())
		throw "Relation arity mismatch!";

	_rels.insert(make_pair(ps, r));
}

Function* Structure::getFunction(const FunctionSymbol &fs) const
{
	auto it = _funs.find(fs);

	if(it == _funs.end())
		throw "Unknown symbol!";

	return it->second;
}

Relation* Structure::getRelation(const PredicateSymbol &ps) const
{
	auto it = _rels.find(ps);

	if(it == _rels.end())
		throw "Unknown symbol!";

	return it->second;
}

/* class Valuation */
Valuation::Valuation(const Domain &dom) : _dom(dom)
{

}

const Domain& Valuation::getDomain() const
{
	return _dom;
}

void Valuation::setValue(const Variable &v, unsigned val)
{
	auto it = find(_dom.begin(), _dom.end(), val);

	if(it == _dom.end())
		throw "Value not in domain!";

	_values.insert(make_pair(v, val));
}

unsigned Valuation::getValue(const Variable &v) const
{
	auto it = _values.find(v);

	if(it == _values.end())
		throw "Unknown variable!";

	return it->second;
}

/* class BaseFormula */
bool BaseFormula::containsVar(const Variable &v, bool free) const
{
	VariableSet vs;

	getVars(vs, free);

	return vs.find(v) != vs.end();
}

/* class AtomicFormula */
unsigned AtomicFormula::complexity() const
{
	return 0;
}

/* class LogicConstant */
bool LogicConstant::equalTo(const Formula &f) const
{
	return getType() == f->getType();
}

void LogicConstant::getVars(VariableSet &vs, bool free) const
{

}

Formula LogicConstant::substitute(const Variable &v, const Term &t)
{
	return shared_from_this();
}

/* class True */
void True::print(ostream &ostr) const
{
	ostr << "TRUE";
}
	
BaseFormula::Type True::getType() const
{
	return T_TRUE;
}

bool True::eval(const Structure &st, const Valuation &v) const
{
	return true;
}

/* class False */
void False::print(ostream &ostr) const
{
	ostr << "FALSE";
}

BaseFormula::Type False::getType() const
{
	return T_FALSE;
}

bool False::eval(const Structure &st, const Valuation &v) const
{
	return false;
}

/* class Atom */
Atom::Atom(const Signature &sig, const PredicateSymbol &p, const vector<Term> &ops) : _sig(sig), _p(p), _ops(ops)
{
	unsigned arity;
	if(!sig.checkPredicateSymbol(p, arity) || arity != ops.size())
		throw "Syntax error.";
}

Atom::Atom(const Signature &sig, const PredicateSymbol &p, vector<Term> &&ops) : _sig(sig), _p(p), _ops(move(ops))
{
	unsigned arity;
	if(!sig.checkPredicateSymbol(p, arity) || arity != _ops.size())
		throw "Syntax error.";
}

const PredicateSymbol& Atom::getSymbol() const
{
	return _p;
}

const Signature& Atom::getSignature() const
{
	return _sig;
}

const vector<Term>& Atom::getOperands() const
{
	return _ops;
}

void Atom::print(ostream &ostr) const
{
	ostr << _p;

	for(int i = 0; i < _ops.size(); i++) {
		if(i == 0)
			ostr << "(";
		else
			ostr << ",";
		ostr <<  _ops[i];
	}

	if(_ops.size() != 0)
		ostr << ")";
}

BaseFormula::Type Atom::getType() const
{
	return T_ATOM;
}

bool Atom::eval(const Structure &st, const Valuation &v) const
{
	Relation *r = st.getRelation(_p);
	vector<unsigned> args;

	for(int i = 0; i < _ops.size(); i++)
		args.push_back(_ops[i]->eval(st, v));

	return r->eval(args);
}

bool Atom::equalTo(const Formula &f) const
{
	if(f->getType() != T_ATOM || _p != ((Atom*) f.get())->getSymbol())
		return false;

	const vector<Term> &ops = ((Atom*) f.get())->getOperands();

	if(ops.size() != _ops.size())
		return false;

	for(int i = 0; i < _ops.size(); i++)
		if(!_ops[i]->equalTo(ops[i]))
			return false;
	return true;
}

void Atom::getVars(VariableSet &vs, bool free) const
{
	for(int i = 0; i < _ops.size(); i++)
		_ops[i]->getVars(vs);
}

Formula Atom::substitute(const Variable &v, const Term &t)
{
	vector<Term> sub_ops;

	for(int i = 0; i < _ops.size(); i++)
		sub_ops.push_back(_ops[i]->substitute(v, t));

	return make_shared<Atom>(_sig, _p, sub_ops);
}

/* class UnaryConnective */
UnaryConnective::UnaryConnective(const Formula &op) : _op(op)
{

}

const Formula& UnaryConnective::getOperand() const
{
	return _op;
}

unsigned UnaryConnective::complexity() const
{
	return _op->complexity() + 1;
}

bool UnaryConnective::equalTo(const Formula &f) const
{
	return f->getType() == getType() && ((UnaryConnective*) f.get())->getOperand()->equalTo(_op);
}

void UnaryConnective::getVars(VariableSet &vs, bool free) const
{
	_op->getVars(vs, free);
}

/* class Not */
void Not::print(ostream &ostr) const
{
	ostr << "¬" << _op;
}

BaseFormula::Type Not::getType() const
{
	return T_NOT;
}

bool Not::eval(const Structure &st, const Valuation &v) const
{
	return !_op->eval(st, v);
}

Formula Not::substitute(const Variable &v, const Term &t)
{
	return make_shared<Not>(_op->substitute(v, t));
}

/* class BinaryConnective */
BinaryConnective::BinaryConnective(const Formula &op1, const Formula &op2) : _op1(op1), _op2(op2)
{

}

const Formula& BinaryConnective::getOperand1() const
{
	return _op1;
}

const Formula& BinaryConnective::getOperand2() const
{
	return _op2;
}

unsigned BinaryConnective::complexity() const
{
	return _op1->complexity() + _op2->complexity() + 1;
}

bool BinaryConnective::equalTo(const Formula &f) const
{
	return f->getType() == getType()
		&& ((BinaryConnective*) f.get())->getOperand1()->equalTo(_op1) && ((BinaryConnective*) f.get())->getOperand2()->equalTo(_op2);
}

void BinaryConnective::getVars(VariableSet &vs, bool free) const
{
	_op1->getVars(vs, free);
	_op2->getVars(vs, free);
}

/* class And */
void And::print(ostream &ostr) const
{
	ostr << "(" << _op1 << " /\\ " << _op2 << ")";
}

BaseFormula::Type And::getType() const
{
	return T_AND;
}

bool And::eval(const Structure &st, const Valuation &v) const
{
	return _op1->eval(st, v) && _op2->eval(st, v);
}

Formula And::substitute(const Variable &v, const Term &t)
{
	return make_shared<And>(_op1->substitute(v, t), _op2->substitute(v, t));
}

/* class Or */
void Or::print(ostream &ostr) const
{
	ostr << "(" << _op1 << " \\/ " << _op2 << ")";
}

BaseFormula::Type Or::getType() const
{
	return T_OR;
}

bool Or::eval(const Structure &st, const Valuation &v) const
{
	return _op1->eval(st, v) || _op2->eval(st, v);
}

Formula Or::substitute(const Variable &v, const Term &t)
{
	return make_shared<Or>(_op1->substitute(v, t), _op2->substitute(v, t));
}

/* class Imp */
void Imp::print(ostream &ostr) const
{
	ostr << "(" << _op1 << " => " << _op2 << ")";
}

BaseFormula::Type Imp::getType() const
{
	return T_IMP;
}

bool Imp::eval(const Structure &st, const Valuation &v) const
{
	return !_op1->eval(st, v) || _op2->eval(st, v);
}

Formula Imp::substitute(const Variable &v, const Term &t)
{
	return make_shared<Imp>(_op1->substitute(v, t), _op2->substitute(v, t));
}

/* class Iff */
void Iff::print(ostream &ostr) const
{
	ostr << "(" << _op1 << " <=> " << _op2 << ")";
}

BaseFormula::Type Iff::getType() const
{
	return T_IFF;
}

bool Iff::eval(const Structure &st, const Valuation &v) const
{
	return _op1->eval(st, v) == _op2->eval(st, v);
}

Formula Iff::substitute(const Variable &v, const Term &t)
{
	return make_shared<Iff>(_op1->substitute(v, t), _op2->substitute(v, t));
}

/* class Quantifier */
const Variable& Quantifier::getVariable() const
{
	return _v;
}

const Formula& Quantifier::getOperand() const
{
	return _op;
}

Quantifier::Quantifier(const Variable &v, const Formula &f) : _v(v), _op(f)
{

}

unsigned Quantifier::complexity() const
{
	return _op->complexity() + 1;
}

bool Quantifier::equalTo(const Formula &f) const
{
	return getType() == f->getType()
		&& ((Quantifier*) f.get())->getOperand()->equalTo(_op) && ((Quantifier*) f.get())->getVariable() == _v;
}

void Quantifier::getVars(VariableSet &vs, bool free) const
{
	bool present = false;
	if(free) {
		if(vs.find(_v) != vs.end())
			present = true;
	}

	_op->getVars(vs, free);

	if(free) {
		if(!present && vs.find(_v) != vs.end())
			vs.erase(_v);
	} else {
		vs.insert(_v);
	}
}

/* class Forall */
void Forall::print(ostream &ostr) const
{
	ostr << "(A " << _v << ").(" << _op << ")";
}

BaseFormula::Type Forall::getType() const
{
	return T_FORALL;
}

bool Forall::eval(const Structure &st, const Valuation &v) const
{
	Valuation nv = v;

	for(int i = 0; i < st.getDomain().size(); i++) {
		nv.setValue(_v, st.getDomain()[i]);

		if(!_op->eval(st, nv))
			return false;
	}

	return true;
}

Formula Forall::substitute(const Variable &v, const Term &t)
{
	if(v == _v)
		return shared_from_this();

	if(t->containsVar(_v)) {
		Variable nv = getUniqueVariable(shared_from_this(), t);
		Formula nf = _op->substitute(_v, make_shared<VariableTerm>(nv));
		return make_shared<Forall>(nv, nf->substitute(v, t));
	}

	return make_shared<Forall>(_v, _op->substitute(v, t));
}

/* class Exists */
void Exists::print(ostream &ostr) const
{
	ostr << "(E " << _v << ").(" << _op << ")";
}

BaseFormula::Type Exists::getType() const
{
	return T_EXISTS;
}

bool Exists::eval(const Structure &st, const Valuation &v) const
{
	Valuation nv = v;

	for(int i = 0; i < st.getDomain().size(); i++) {
		nv.setValue(_v, st.getDomain()[i]);

		if(_op->eval(st, nv))
			return true;
	}

	return false;
}

Formula Exists::substitute(const Variable &v, const Term &t)
{
	if(v == _v)
		return shared_from_this();

	if(t->containsVar(_v)) {
		Variable nv = getUniqueVariable(shared_from_this(), t);
		Formula nf = _op->substitute(_v, make_shared<VariableTerm>(nv));
		return make_shared<Exists>(nv, nf->substitute(v, t));
	}

	return make_shared<Exists>(_v, _op->substitute(v, t));
}

/* Helper functions */
Variable getUniqueVariable(const Formula &f, const Term &t)
{
	static unsigned i = 0;

	Variable v;

	do {
		v = string("uv") + to_string(++i);
	} while(t->containsVar(v) || f->containsVar(v));

	return v;
}

/* Test */
class Plus : public Function
{
	public:
		Plus() : Function(2) { }

		unsigned eval(const vector<unsigned> &args = vector<unsigned>()) const {
			if(args.size() != getArity())
				throw "Syntax error";

			return (args[0] + args[1]) % 5;
		}
};

class One : public Function
{
	public:
		One() : Function(0) { }

		unsigned eval(const vector<unsigned> &args) const {
			if(args.size() != getArity())
				throw "Syntax error";

			return 1;
		}
};

class P : public Relation
{
	public:
		P() : Relation(1) { }

		bool eval(const vector<unsigned> &args) const {
			if(args.size() != getArity())
				throw "Syntax error";

			return args[0] % 2 == 0;
		}
};

int main()
{
	try {
		Domain d = Domain { 0, 1, 2, 3, 4 };

		Signature sig;
		sig.addFunctionSymbol("add5", 2);
		sig.addFunctionSymbol("1", 0);
		sig.addPredicateSymbol("P", 1);

		Structure st(sig, d);
		st.addFunction("add5", new Plus());
		st.addFunction("1", new One());
		st.addRelation("P", new P());

		Term t1 = make_shared<FunctionTerm>(sig, "1"); 
		Term t2 = make_shared<VariableTerm>("x");
		Term t3 = make_shared<FunctionTerm>(sig, "add5", vector<Term> { t1, t2 });
		Term t4 = make_shared<VariableTerm>("y");
		Term t5 = make_shared<FunctionTerm>(sig, "add5", vector<Term> { t2, t4 });

		Formula f1 = make_shared<Atom>(sig, "P", vector<Term> { t3 });
		Formula f2 = make_shared<Atom>(sig, "P", vector<Term> { t5 });
		Formula f3 = make_shared<Not>(f1);
		Formula f4 = make_shared<And>(f2, f3);
		Formula f5 = make_shared<Exists>("y", f4);
		Formula f6 = make_shared<Forall>("x", f5);

		Valuation v(d);
		v.setValue("x", 2);
		v.setValue("y", 3);

		cout << f6 << endl;
		cout << f6->eval(st, v);
	} catch (const char* e) { cout << e << endl; }

	return 0;
}
