CC = g++
FLAGS = -std=c++14
PROG = iskazna_logika

$(PROG) : main.o Valuation.o Formula.o AtomicFormula.o LogicConstant.o True.o False.o Atom.o BinaryConnective.o And.o Or.o Iff.o Imp.o UnaryConnective.o Not.o
	$(CC) $(FLAGS) -o $@ $^

main.o : main.cpp Valuation.h Formula.h AtomicFormula.h Atom.h LogicConstant.h True.h False.h UnaryConnective.h Not.h BinaryConnective.h And.h Or.h Imp.h Iff.h
	$(CC) $(FLAGS) -c -o $@ $<

Valuation.o : Valuation.cpp Valuation.h
	$(CC) $(FLAGS) -c -o $@ $<

Formula.o : Formula.cpp Formula.h Valuation.h
	$(CC) $(FLAGS) -c -o $@ $<

AtomicFormula.o : AtomicFormula.cpp AtomicFormula.h Formula.h Valuation.h
	$(CC) $(FLAGS) -c -o $@ $<

LogicConstant.o : LogicConstant.cpp LogicConstant.h AtomicFormula.h Formula.h Valuation.h
	$(CC) $(FLAGS) -c -o $@ $<

True.o : True.cpp True.h LogicConstant.h AtomicFormula.h Formula.h Valuation.h
	$(CC) $(FLAGS) -c -o $@ $<

False.o : False.cpp False.h LogicConstant.h AtomicFormula.h Formula.h Valuation.h
	$(CC) $(FLAGS) -c -o $@ $<

Atom.o : Atom.cpp Atom.h AtomicFormula.h Formula.h Valuation.h
	$(CC) $(FLAGS) -c -o $@ $<

BinaryConnective.o : BinaryConnective.cpp BinaryConnective.h Formula.h Valuation.h 
	$(CC) $(FLAGS) -c -o $@ $<

And.o : And.cpp And.h BinaryConnective.h Formula.h Valuation.h False.h LogicConstant.h AtomicFormula.h
	$(CC) $(FLAGS) -c -o $@ $<

Or.o : Or.cpp Or.h BinaryConnective.h Formula.h Valuation.h True.h LogicConstant.h AtomicFormula.h 
	$(CC) $(FLAGS) -c -o $@ $<

Iff.o : Iff.cpp Iff.h BinaryConnective.h Formula.h Valuation.h True.h Not.h And.h Or.h UnaryConnective.h LogicConstant.h AtomicFormula.h
	$(CC) $(FLAGS) -c -o $@ $<

Imp.o : Imp.cpp Imp.h BinaryConnective.h Formula.h Valuation.h True.h Not.h Or.h LogicConstant.h AtomicFormula.h UnaryConnective.h
	$(CC) $(FLAGS) -c -o $@ $<

UnaryConnective.o : UnaryConnective.cpp UnaryConnective.h Formula.h Valuation.h
	$(CC) $(FLAGS) -c -o $@ $<

Not.o : Not.cpp Not.h UnaryConnective.h Formula.h Valuation.h True.h False.h LogicConstant.h AtomicFormula.h And.h Or.h Iff.h Imp.h UnaryConnective.h
	$(CC) $(FLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f *.o *.swp $(PROG)
