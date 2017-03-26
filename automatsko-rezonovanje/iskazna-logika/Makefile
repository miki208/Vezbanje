CC = g++
FLAGS = -std=c++14
PROG = iskazna_logika

$(PROG) : main.o Valuation.o Formula.o AtomicFormula.o LogicConstant.o True.o
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

.PHONY: clean

clean:
	rm -f *.o *.swp $(PROG)
