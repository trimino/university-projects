CXXFLAGS = --std=c++17


all: color


color: main.o color.o color.h
	$(CXX) $(CXXFLAGS) main.o color.o -o color


color.o: color.cpp color.h
	$(CXX) $(CXXFLAGS) -c color.cpp color.h


clean:
	rm -f *.o *.gch ~* a.out color






