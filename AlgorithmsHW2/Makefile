CC = g++
FLAGS = -g
SRC = main.cpp sorts.cpp helper.cpp
OBJ = main.o sorts.o helper.o
EXEC = run

all: $(EXEC)

$(EXEC): $(OBJ) 
	$(CC) $(FLAGS) -o $(EXEC) $(OBJ)

.cpp.o: $(CC) $(FLAGS) -c $< -o $@

clean: rm -f $(EXEC) $(OBJ)
