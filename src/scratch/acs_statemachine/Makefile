# Makefile for the design and test of
# the OreSat ACS state machine

CC = gcc

# binaries
PROG_BIN = acs_statemachine
TEST_BIN = acs_test

SRC = ./src
INC = ./inc

PROG_CFLAGS=
TEST_CFLAGS=
FLAGS=-I $(INC) -g -Wall -Wextra 

# sources
PROG_SRCS=$(SRC)/statemachine_main.c \
					$(SRC)/statemachine.c 

TEST_SRCS=$(SRC)/test_main.c \
					$(SRC)/test.c 

# headers
PROG_INC=$(INC)
TEST_INC=$(INC) 

PROG_OBJS = $(PROG_SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)

default: $(PROG_BIN) $(TEST_BIN)
	@echo build successful!
 
$(PROG_BIN): $(PROG_OBJS)
	$(CC) $(PROG_CFLAGS) -o $(PROG_BIN) $(PROG_OBJS)
	@echo $(PROG_BIN) compiled!

$(TEST_BIN): $(TEST_OBJS)
	$(CC) $(TEST_CFLAGS) -o $(TEST_BIN) $(TEST_OBJS)
	@echo $(TEST_BIN) compiled!

.c.o: 
	$(CC) $(FLAGS) -c $^ -o $@

run:
	./$(PROG_BIN)

test:
	./$(TEST_BIN)

clean: 
	rm -f $(SRC)/*.o \
		*.o \
		$(PROG_BIN) \
		$(TEST_BIN)

valgrind: $(BIN)
	valgrind --leak-check=full \
		./$(PROG_BIN)
		./$(TEST_BIN)
