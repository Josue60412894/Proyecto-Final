#
# Makefile for the server socket programming
#

SERVER_SRC=src/_main.cpp socket/ServerSocket.cpp socket/Socket.cpp socket/ListenClient.cpp sqlite/SQLiteManagement.cpp sqlite/SQLitemMenu.cpp sqlite/RequestHandler.cpp  src/WriteTextFile.cpp -lsqlite3
INCLUDE_FOLDERS=-Iinclude
BIN_EXE=bin/server

.PHONY: all
all: server

#
# This will run the server
# if the project is not compiled then this will fail
#
run_server:
	./${BIN_EXE}

bin_folder:
	mkdir -p bin

#
# This will create the server binary file
# It is located at the bin folder
#
server: $(bin_folder)
	g++ ${INCLUDE_FOLDERS} -o ${BIN_EXE} ${SERVER_SRC}

.PHONY: clean
clean:
	rm -f bin/server
