CC = g++
FLAGS = -std=c++14
PROG = iskazna_logika

$(PROG) : main.o Valuation.o Formula.o AtomicFormula.o LogicConstant.o True.o False.o Atom.o BinaryConnective.o And.o Or.o
	$(CC) $(FLAGS) -o $@ $^

main.o : main.cpp
	$(CC) $(FLAGS) -c -o $@ $^

Valuation.o : Valuation.cpp Valuation.h
	$(CC) $(FLAGS) -c -o $@ $<

Formula.o : Formula.cpp Formula.h
	$(CC) $(FLAGS) -c -o $@ $<

AtomicFormula.o : AtomicFormula.cpp AtomicFormula.h
	$(CC) $(FLAGS) -c -o $@ $<

LogicConstant.o : LogicConstant.cpp Formula.h AtomicFormula.h LogicConstant.h
	$(CC) $(FLAGS) -c -o $@ $<

True.o : True.cpp Formula.h AtomicFormula.h LogicConstant.h True.h
	$(CC) $(FLAGS) -c -o $@ $<

False.o : False.cpp Formula.h AtomicFormula.h LogicConstant.h False.h
	$(CC) $(FLAGS) -c -o $@ $<

Atom.o : Atom.cpp Formula.h AtomicFormula.h Atom.h
	$(CC) $(FLAGS) -c -o $@ $<

BinaryConnective.o : BinaryConnective.cpp Formula.h
	$(CC) $(FLAGS) -c -o $@ $<

And.o : And.cpp Formula.h BinaryConnective.h And.h
	$(CC) $(FLAGS) -c -o $@ $<

Or.o : Or.cpp Formula.h BinaryConnective.h Or.h
	$(CC) $(FLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f *.o *.swp $(PROG)
