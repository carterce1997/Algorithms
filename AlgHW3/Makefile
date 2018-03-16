SOURCE = node.cpp bst.cpp avl.cpp splay.cpp main.cpp
OBJS = node.o bst.o avl.o splay.o main.o
CC = g++
TARGET = test_me

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

clean:
	rm -f $(TARGET)
