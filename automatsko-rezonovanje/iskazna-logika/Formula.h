#ifndef _FORMULA_H_
#define _FORMULA_H_

#include <memory>
#include <iostream>
#include <set>
#include "Valuation.h"

class BaseFormula;

typedef std::shared_ptr<BaseFormula> Formula;
typedef std::set<unsigned> AtomSet;

enum Type {T_TRUE, T_FALSE, T_AND, T_OR, T_NOT, T_IFF, T_IMP, T_ATOM};

class BaseFormula : public std::enable_shared_from_this<BaseFormula>
{
	public:
	virtual Type getType() const = 0;
	virtual int complexity() const = 0;
	virtual void print(std::ostream&) const = 0;
	virtual bool equalsTo(const Formula&) const = 0;
	virtual void getAtoms(AtomSet&) const = 0;
	virtual Formula substitute(const Formula&, const Formula&) = 0;
	virtual bool eval(const Valuation&) const = 0;
	bool issat(Valuation&) const;
	bool isTautology() const;
	void printTruthTable() const;
	bool isConsequence(const Formula&) const;
	bool isEquivalent(const Formula&) const;
	virtual Formula simplify() = 0;
	virtual Formula nnf() = 0;
};

std::ostream& operator << (std::ostream&, const Formula&);

#endif
