 
CXXFLAGS += --std=c++17
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

all: mainwin

debug: CXXFLAGS += -g
debug: mainwin

mainwin: main.o mainwin.o entrydialog.o store.o customer.o desktop.o options.o order.o 
	$(CXX) $(CXXFLAGS) main.o mainwin.o entrydialog.o store.o customer.o desktop.o options.o order.o $(GTKFLAGS) -o elsa

main.o: main.cpp *.h
	$(CXX) $(CXXFLAGS) -c main.cpp $(GTKFLAGS) -o main.o

mainwin.o: mainwin.cpp *.h
	$(CXX) $(CXXFLAGS) -c mainwin.cpp $(GTKFLAGS) -o mainwin.o

entrydialog.o: entrydialog.cpp *.h
	$(CXX) $(CXXFLAGS) -c entrydialog.cpp $(GTKFLAGS) -o entrydialog.o

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
