SRC=src
TEST_DIR=tests
LIB_DIR=lib
CXX=g++
WARNINGS=-Wall -Werror

# compile python library
${LIB_DIR}/libtinystepperdriver.so: ${LIB_DIR}/tinystepperdriver.o 
	${CXX} ${WARNINGS} -shared -Wl,-soname,libtinystepperdriver.so -fPIC ${LIB_DIR}/tinystepperdriver.o ${LIB_DIR}/mock/Arduino.h -o ${LIB_DIR}/libtinystepperdriver.so

${LIB_DIR}/tinystepperdriver.o: ${SRC}/tinystepperdriver.cpp ${SRC}/tinystepperdriver.hpp ${LIB_DIR}/mock/Arduino.h
	${CXX} ${WARNINGS} -I${LIB_DIR}/mock -fPIC -DTINYSTEPPERDRIVER_PYTHON_BIND -DTINYSTEPPERDRIVER_DEBUG -c ${SRC}/*.cpp -o ${LIB_DIR}/tinystepperdriver.o
