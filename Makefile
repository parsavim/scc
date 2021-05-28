SRC_DIR := src
INC_DIR := include
BIN_DIR := bin

SRCS := $(wildcard $(SRC_DIR)/*.c)
BINS := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))

TESTS_DIR := tests
TESTS_SRC_DIR := $(TESTS_DIR)/src
TESTS_BIN_DIR := $(TESTS_DIR)/bin

TEST_SRCS := $(wildcard $(TESTS_SRC_DIR)/*.c)
TEST_BINS := $(patsubst $(TESTS_SRC_DIR)/%.c, $(TESTS_BIN_DIR)/%, $(TEST_SRCS))

PREFIX := /usr

LIB := $(BIN_DIR)/libscc.a 

OPTLVL := 0
CFLAGS := -O$(OPTLVL) -Wall -Werror -I$(INC_DIR) -I$(PREFIX)/include

CC ?= gcc
AR ?= ar

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ -c $(CFLAGS) $<

$(TESTS_BIN_DIR)/%: $(TESTS_SRC_DIR)/%.c $(LIB)
	$(CC) -o $@ $(CFLAGS) $< -L$(BIN_DIR) -lscc 

$(LIB): $(BINS)
	$(AR) rcs $@ $^

.PHONY = tests run_tests

define \n


endef
tests: $(TEST_BINS)
	$(foreach TEST, $^, ./$(TEST)$(\n))

