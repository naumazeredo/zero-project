EXEC = zero.out

CC = g++
CC_FLAGS = -Wall -std=c++11
LD_FLAGS = -lSDL2 -lSDL2_image

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))

all: $(EXEC) run

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LD_FLAGS)

obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CC) $(CC_FLAGS) -c -o $@ $<


.PHONY: clean run
clean:
	@rm -rf $(EXEC) obj

rebuild: clean $(EXEC)

run:
	./$(EXEC)

