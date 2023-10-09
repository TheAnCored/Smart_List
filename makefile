GPP = g++
CFLAG = -c
OFLAG = -o
WALLFLAG = -Wall

alt: my_prog

main.o: main.cpp
	$(GPP) $(CFLAG) $(WALLFLAG) main.cpp

autotests.o: autotests.cpp
	$(GPP) $(CFLAG) $(WALLFLAG) autotests.cpp

unidirectional_list.o: unidirectional_list.cpp
	$(GPP) $(CFLAG) $(WALLFLAG) unidirectional_list.cpp

functions.o: functions.cpp
	$(GPP) $(CFLAG) $(WALLFLAG) functions.cpp

my_prog: main.o autotests.o unidirectional_list.o functions.o
	$(GPP) main.o autotests.o unidirectional_list.o functions.o $(OFLAG) my_prog

clear:
	rm -rf *.o my_prog