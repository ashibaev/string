.PHONY: all refresh clean

CXXFLAGS=$(WARN_OPTS) $(INCLUDES) $(FLAGS) -std=c++11

LDFLAGS=$(FLAGS) -lm -lpthread

MAIN=main.cpp
MAIN_OBJECT=$(MAIN:.cpp=.o)
SOURCES=String.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TEST_SOURCES=test_main.cpp $(SOURCES:.cpp=_ut.cpp)
TEST_OBJECTS=$(TEST_SOURCES:.cpp=.o)

all: check main clean.o

refresh: clean all

clean: clean.o
	rm -rf main check

clean.o:
	rm -rf *.o

main: $(MAIN_OBJECT) $(OBJECTS)
	$(LD) -o main $(MAIN_OBJECT) $(OBJECTS)


check: $(OBJECTS) $(TEST_OBJECTS)
	$(LD) -o check $(OBJECTS) $(TEST_OBJECTS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@
