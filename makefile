SRC = tinystepperdriver
TEST_DIR = tests
LIB_DIR = lib
CXX = g++
WARNINGS = -Wall -Werror

# distinct system
ifdef OS
	RM = del /Q
	FixPath = $(subst /,\,$1)
	EXEC_POST = exe
else
	RM = rm -f
	FixPath = $1
	EXEC_POST = a
endif

all: tests lib cleanup

# Compile python library
lib: tests ${LIB_DIR}/tinystepperdriver.o 
	${CXX} ${WARNINGS} -shared -Wl,-soname,libtinystepperdriver.so -fPIC ${LIB_DIR}/tinystepperdriver.o ${LIB_DIR}/mock/Arduino.h -o ${LIB_DIR}/libtinystepperdriver.so

${LIB_DIR}/tinystepperdriver.o: ${SRC}/tinystepperdriver.cpp ${SRC}/tinystepperdriver.hpp ${LIB_DIR}/mock/Arduino.h
	${CXX} ${WARNINGS} -I${LIB_DIR}/mock -fPIC -DTINYSTEPPERDRIVER_PYTHON_BIND -DTINYSTEPPERDRIVER_DEBUG -c ${SRC}/*.cpp -o ${LIB_DIR}/tinystepperdriver.o

# Compile and execute tests. make exits on return codes != 0
tests: ${TEST_DIR}/test_tinystepperdriver.${EXEC_POST}
	${TEST_DIR}/test_tinystepperdriver.${EXEC_POST}

${TEST_DIR}/test_tinystepperdriver.${EXEC_POST}: ${TEST_DIR}/tinystepperdriver.o ${TEST_DIR}/test_tinystepperdriver.cpp ${TEST_DIR}/mock/Arduino.cpp
	${CXX} ${WARNINGS} -I${TEST_DIR}/mock -I${SRC} ${TEST_DIR}/test_tinystepperdriver.cpp ${TEST_DIR}/tinystepperdriver.o ${TEST_DIR}/mock/Arduino.cpp -o ${TEST_DIR}/test_tinystepperdriver.${EXEC_POST}

${TEST_DIR}/tinystepperdriver.o:  ${SRC}/tinystepperdriver.cpp ${SRC}/tinystepperdriver.hpp ${TEST_DIR}/mock/Arduino.h
	${CXX} ${WARNINGS} -I${TEST_DIR}/mock -fPIC -c ${SRC}/*.cpp -o ${TEST_DIR}/tinystepperdriver.o

# Remove intermediate files
cleanup: lib tests
	${RM} $(call FixPath,${TEST_DIR}/tinystepperdriver.o)
	${RM} $(call FixPath,${LIB_DIR}/tinystepperdriver.o)