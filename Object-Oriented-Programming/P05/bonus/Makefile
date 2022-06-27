#Makefile for regression test
CXXFLAGS+= --std=c++17

all: test

test: test.o product.o taxed.o taxfree.o
	$(CXX) $(CXXFLAGS) test.o product.o taxed.o taxfree.o -o test

test.o: test.cpp *.h
	$(CXX) $(CXXFLAGS) test.cpp -c -o test.o

product.o: product.cpp *.h
	$(CXX) $(CXXFLAGS) product.cpp -c -o product.o

taxed.o: taxed.cpp *.h
	$(CXX) $(CXXFLAGS) taxed.cpp -c -o taxed.o

taxfree.o: taxfree.cpp *.h
	$(CXX) $(CXXFLAGS) taxfree.cpp -c -o taxfree.o

clean:
	-rm -f *.o *.gch *~test
