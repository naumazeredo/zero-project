EXEC = bin/zero

CC = g++
CC_FLAGS = -Wall -std=c++11
LD_FLAGS = -lsfml-window -lsfml-graphics -lsfml-system

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))

$(EXEC): $(OBJECTS)
	@mkdir -p bin
	$(CC) -o $@ $^ $(LD_FLAGS)

obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CC) $(CC_FLAGS) -c -o $@ $<

.PHONY: clean run
clean:
	@rm -rf $(EXEC) obj

run:
	./$(EXEC)

