CC = g++
FLAGS = -g
SRC = main.cpp search.cpp helper.cpp
OBJ = main.o search.o helper.o
EXEC = run

all: $(EXEC)

$(EXEC): $(OBJ) 
	$(CC) $(FLAGS) -o $(EXEC) $(OBJ)

.cpp.o: $(CC) $(FLAGS) -c $< -o $@

clean: rm -f $(EXEC) $(OBJ)
