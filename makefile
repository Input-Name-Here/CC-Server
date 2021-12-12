OBJS = main.cpp colour.cpp

CC = g++

COMPILER_FLAGS = -w

LINKER_FLAGS = # in case you want to add some libraries, add the -l flags here
COMPILER_FLAGS = # add -g to debug with gdb

OBJ_NAME = program

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
