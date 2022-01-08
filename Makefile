OBJS = src/*.cpp
CC = g++

ifeq ($(OS), Windows_NT)
	LIBRARY_PATHS = -LC:/MinGW/bin/g++.exe
endif 

COMPILER_FLAGS = -Werror -Wfloat-conversion -ggdb -g 

LINKER_FLAGS = 0

ifeq ($(OS), Windows_NT)
	LINKER_FLAGS = -lmingw32
else
	LINKER_FLAGS = -lm
endif

OBJ_NAME = emulator

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)