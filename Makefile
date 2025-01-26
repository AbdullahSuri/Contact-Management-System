cms.out: contact.o main.o myvector.o contactbst.o
	g++ contact.o main.o myvector.o contactbst.o -o cms.out
main.o: main.cpp
	g++ -c main.cpp
contact.o: contact.cpp contact.h
	g++ -c contact.cpp
myvector.o: myvector.cpp myvector.h
	g++ -c myvector.cpp
contactbst.o: contactbst.cpp contactbst.h
	g++ -c contactbst.cpp
clean:
	rm *.o *.out

