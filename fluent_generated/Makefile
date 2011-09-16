a.out : fluent_simple.cpp transitions.h transitions.o
	g++ fluent_simple.cpp transitions.o

transitions.o : transitions.h transitions.cpp 
	g++ -c transitions.cpp

transitions.h transitions.cpp : transition_table.txt helper.py
	python helper.py
