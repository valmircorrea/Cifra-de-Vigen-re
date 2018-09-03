LIB_DIR = ./lib
INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./build
BIN_DIR = ./bin
DOC_DIR = ./doc
DATA_DIR = ./data/mensagens_decifradas

CC = g++
CPPLAGS = -Wall -pedantic -ansi -std=c++11 -I. -I$(INC_DIR)

RM = rm -rf
RM_TUDO = rm -fr

PROG = decifra
PROG2 = cifra

.PHONY: all clean debug doc doxygen gnuplot init valgrind

all: init $(PROG) $(PROG2)

debug: CFLAGS += -g -O0
debug: $(PROG) $(PROG2)

init:
	@mkdir -p $(BIN_DIR)/
	@mkdir -p $(OBJ_DIR)/

########################## DECIFRA #########################
$(PROG): $(OBJ_DIR)/decifra.o
	@echo "====================================================="
	@echo "Ligando o alvo $@"
	@echo "====================================================="		
	$(CC) $(CPPLAGS) -o $(BIN_DIR)/$@ $^
	@echo "*** [Executavel $(PROG) criado em $(BIN_DIR)] ***"
	@echo "====================================================="

$(OBJ_DIR)/decifra.o: $(SRC_DIR)/decifra.cpp
	$(CC) -c $(CPPLAGS) -o $@ $<

########################## CIFRA #########################
$(PROG2): $(OBJ_DIR)/cifra.o
	@echo "====================================================="
	@echo "Ligando o alvo $@"
	@echo "====================================================="		
	$(CC) $(CPPLAGS) -o $(BIN_DIR)/$@ $^
	@echo "*** [Executavel $(PROG) criado em $(BIN_DIR)] ***"
	@echo "====================================================="

$(OBJ_DIR)/cifra.o: $(SRC_DIR)/cifra.cpp
	$(CC) -c $(CPPLAGS) -o $@ $<
clean:
	@echo "====================================================="
	@echo "Limpando pastas $(BIN_DIR) e $(OBJ_DIR)"
	@echo "====================================================="
	$(RM) $(BIN_DIR)/*
	$(RM) $(OBJ_DIR)/*
	$(RM) $(DATA_DIR)/*