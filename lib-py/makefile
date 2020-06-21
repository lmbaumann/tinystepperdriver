tinystepperdriver.so: tinystepperdriver.o
	g++ -shared -Wl,-soname,libtinystepperdriver.so -o libtinystepperdriver.so  tinystepperdriver.o

tinystepperdriver.o: ../tinystepperdriver.cpp ../tinystepperdriver.hh lib/Arduino.h
	g++ -Wall -Ilib -DTINYSTEPPERDRIVER_PYTHON_BIND -c -fPIC ../tinystepperdriver.cpp -o tinystepperdriver.o