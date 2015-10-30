SOURCES=src/main.cpp src/hanoi.cpp
OBJECTS=$(SOURCES:.cpp=.o)

CXXFLAGS=--std=c++14 -I./include -Wall -Wextra -Werror

bin/hanoi: $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS)