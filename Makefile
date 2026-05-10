CC=gcc
CFLAGS=-g -Wall
BUILD=build
SRC=$(shell find . -name "*.c")
BINS=$(patsubst %.c, $(BUILD)/%, $(notdir $(SRC)))

.PHONY: all clean

all: $(BUILD) $(BINS)

$(BUILD):
	@mkdir -p $(BUILD)

VPATH=$(sort $(dir $(SRC)))

$(BUILD)/%: %.c
	@echo "CC: $< -> $@"
	@$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -rf $(BUILD)