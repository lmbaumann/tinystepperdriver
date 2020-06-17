tinystepperdriver.so: tinystepperdriver.o
	g++ -shared -Wl,-soname,libtinystepperdriver.so -o libtinystepperdriver.so  tinystepperdriver.o

tinystepperdriver.o: ../tinystepperdriver.cpp ../tinystepperdriver.hh ../Arduino.h
	g++ -Wall -DC_LIB -c -fPIC ../tinystepperdriver.cpp -o tinystepperdriver.o