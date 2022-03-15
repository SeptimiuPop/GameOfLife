CC = g++
SRC = App/src/*.cpp
INCLUDES = -I "App/headers"
LIBS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system # to link.

BIN_PATH = bin/
EXE_PATH = $(BIN_PATH)main.exe

build:
	clear
	@echo "Building the enviroment...\n"

	@$(CC) -c $(SRC) $(INCLUDES) 
	@$(CC) *.o -o $(EXE_PATH) $(LIBS)

	@mv *.o $(BIN_PATH)

run: build
	@./$(EXE_PATH)

clear:
	@rm $(BIN_PATH)*.o
	@rm $(BIN_PATH)main.exe

