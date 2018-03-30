CC = g++
FLAGS = -g
SRC = main.cpp
OBJ = main.o
EXEC = run

all: $(EXEC)

$(EXEC): $(OBJ) 
	$(CC) $(FLAGS) -o $(EXEC) $(OBJ)

.cpp.o: $(CC) $(FLAGS) -c $< -o $@

clean: 
	rm -f $(EXEC) $(OBJ) 
