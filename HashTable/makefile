project3 : main.o one.o two.o part3.o part4.o
	g++ -std=c++11 -o project3 main.o one.o two.o part3.o part4.o
main.o : main.cpp one.h
	g++ -std=c++11 -c main.cpp
one.o : one.cpp one.h table.h two.h part3.h part4.h
	g++ -std=c++11 -c one.cpp
two.o : two.cpp two.h table.h
	g++ -std=c++11 -c two.cpp
part3.o : part3.cpp part3.h table.h
	g++ -std=c++11 -c part3.cpp
part4.o : part4.cpp part4.h table.h
	g++ -std=c++11 -c part4.cpp
clean :
	rm -f *.o project3

run : project3
	./project3
