CXXFLAGS += --std=c++17

all: coin 

debug: CXXFLAGS += -g
debug: test coin 

logger: CXXFLAGS += -DLOGGER
logger: coin

coin: coin.o test.o *.h
	$(CXX) $(CXXFLAGS) -DLOGGER coin.o test.o -o coin

test.o: test.cpp *.h
	$(CXX) $(CXXFLAGS) -DLOGGER -c test.cpp -o test.o

coin.o: coin.cpp *.h
	$(CXX) $(CXXFLAGS) -DLOGGER -c coin.cpp -o coin.o

clean:
	-rm -f *.o *.gch *~ test



