CC=gcc

PROG_BIN=acs_sm
TEST_BIN=test

PROG_CFLAGS=
TEST_CFLAGS=
FLAGS=-I ./include -g -Wall -Wextra \
			-std=c++11 -Wno-unused-parameter

SRC=./src
INC=./inc

PROG_SRCS=$(SRC)/statemachine.c \

TEST_SRCS=
#TEST_SRCS=$(SRC)/test_main.cpp \
#					$(SRC)/test.cpp \
PROG_INC=

TEST_INC=
#TEST_INC=$(INC)/test.h \

PROG_OBJS = $(PROG_SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

#default: $(PROG_BIN) $(TEST_BIN)
default: $(PROG_BIN) 
	@echo build successful!
 
$(PROG_BIN): $(PROG_OBJS)
	$(CC) $(PROG_CFLAGS) -o $(PROG_BIN) $(PROG_OBJS)
	@echo $(PROG_BIN) compiled!

$(TEST_BIN): $(TEST_OBJS)
	$(CC) $(TEST_CFLAGS) -o $(TEST_BIN) $(TEST_OBJS)
	@echo $(TEST_BIN) compiled!

.cpp.o: 
	$(CC) $(FLAGS) -c $^ -o $@

run_$(PROG_BIN):
	./$(PROG_BIN)

run_test:
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
