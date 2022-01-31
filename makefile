OS	:= 

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= quicksql.exe
else
EXECUTABLE	:= quicksql
endif

all:
	gcc -g ./src/*.c -o $(EXECUTABLE) -lm
