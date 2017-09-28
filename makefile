store: store.o book.o menu.o
	g++ -o store store.o book.o menu.o

store.o: store.cpp store.h
	g++ -c store.cpp

book.o: book.cpp book.h
	g++ -c book.cpp

menu.o: menu.cpp store.h
	g++ -c menu.cpp

clean:
	rm -f *.o mixed
