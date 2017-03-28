#include "LogicConstant.h"

bool LogicConstant::equalsTo(const Formula &f) const
{
	return f->getType() == getType();
}

void LogicConstant::getAtoms(AtomSet &atoms) const
{
}
