#ifndef _VALUATION_H_
#define _VALUATION_H_

#include <iostream>
#include <map>
#include <set>

typedef std::set<unsigned> AtomSet;

class Valuation {
	public:
	bool getValue(unsigned) const;
	void setValue(unsigned, bool);
	void init(const AtomSet&);
	bool next();
	void print(std::ostream&) const;

	private:
	std::map<unsigned, bool> _vars;
};

std::ostream& operator << (std::ostream&, const Valuation&);

#endif
