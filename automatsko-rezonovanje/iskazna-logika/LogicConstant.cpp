#include "LogicConstant.h"

bool LogicConstant::equalsTo(const Formula &f) const
{
	return f->getType() == this->getType();
}

void LogicConstant::getAtoms(AtomSet &atoms) const
{
}
