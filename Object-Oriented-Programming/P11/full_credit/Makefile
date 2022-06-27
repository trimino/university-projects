CXXFLAGS+= --std=c++17

all: shop

shop: main.o cart.o item.o
	$(CXX) $(CXXFLAGS) cart.o item.o main.o -o shop

main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) main.cpp -c -o main.o

cart.o: cart.cpp *.h
	$(CXX) $(CXXFLAGS) cart.cpp -c -o cart.o

item.o: item.cpp *.h
	$(CXX) $(CXXFLAGS) item.cpp -c -o item.o

clean:
	-rm -f *.o *.gch *~shop