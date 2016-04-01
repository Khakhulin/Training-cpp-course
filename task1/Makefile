CC = g++
CFLAGS =  -O2 -std=c++11 -g -Wall  -Werror

SOURCES = set.cpp $(EXECUTABLE).cpp
OBJECTS = $(SOURCES:.cpp = .o)
EXECUTABLE = test

all: $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS)  $(GCOV_F) -o $@ $^
%.o:%.cpp
	$(CC) -c -MD $(CFLAGS) $(GCOV_F) -o $@ $<
-include $(wildcard *.d)
clean:
	rm -f *.o *.d main.out
clean_gcov:
	rm -f *.g*
.PHONY: all clean
