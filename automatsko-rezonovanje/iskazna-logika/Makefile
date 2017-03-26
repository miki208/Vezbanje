CC = g++
FLAGS = -std=c++14
PROG = iskazna_logika

$(PROG) : main.o Formula.o AtomicFormula.o LogicConstant.o True.o
	$(CC) $(FLAGS) -o $@ $^

main.o : main.cpp
	$(CC) $(FLAGS) -c -o $@ $^

Formula.o : Formula.cpp Formula.h
	$(CC) $(FLAGS) -c -o $@ $<

AtomicFormula.o : AtomicFormula.cpp AtomicFormula.h
	$(CC) $(FLAGS) -c -o $@ $<

LogicConstant.o : LogicConstant.cpp LogicConstant.h
	$(CC) $(FLAGS) -c -o $@ $<

True.o : True.cpp True.h
	$(CC) $(FLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f *.o *.swp $(PROG)
