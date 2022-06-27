CXXFLAGS += --std=c++17

all: coin 

debug: CXXFLAGS += -g
debug: test coin 

logger: CXXFLAGS += -DLOGGER
logger: coin

coin: coin.o main.o *.h
	$(CXX) $(CXXFLAGS) -DLOGGER coin.o main.o -o coin

main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

coin.o: coin.cpp *.h
	$(CXX) $(CXXFLAGS) -c coin.cpp -o coin.o

clean:
	-rm -f *.o *.gch *~ test



