CXXFLAGS+= --std=c++17

all: elsa
debug: CXXFLAGS+= -g
debug: elsa

elsa: main.o store.o customer.o desktop.o options.o order.o *.h
	$(CXX) $(CXXFLAGS) main.o store.o customer.o desktop.o options.o order.o -o elsa

main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) main.cpp -c -o main.o

store.o: store.cpp *.h
	$(CXX) $(CXXFLAGS) store.cpp -c -o store.o 

customer.o: customer.cpp *.h
	$(CXX) $(CXXFLAGS) customer.cpp -c -o customer.o

desktop.o: desktop.cpp *.h
	$(CXX) $(CXXFLAGS) desktop.cpp -c -o desktop.o 

options.o: options.cpp *.h
	$(CXX) $(CXXFLAGS) options.cpp -c -o options.o 

order.o: order.cpp *.h
	$(CXX) $(CXXFLAGS) order.cpp -c -o order.o 

clean:
	-rm -f *.o *.gch 