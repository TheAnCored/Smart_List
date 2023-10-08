GPP = g++
CFLAG = -c
OFLAG = -o

alt: my_prog

main.o: main.cpp
	$(GPP) $(CFLAG) main.cpp

autotests.o: autotests.cpp
	$(GPP) $(CFLAG) autotests.cpp

unidirectional_list.o: unidirectional_list.cpp
	$(GPP) $(CFLAG) unidirectional_list.cpp

functions.o: functions.cpp
	$(GPP) $(CFLAG) functions.cpp

my_prog: main.o autotests.o unidirectional_list.o functions.o
	$(GPP) main.o autotests.o unidirectional_list.o functions.o $(OFLAG) my_prog

clear:
	rm -rf *.o my_prog