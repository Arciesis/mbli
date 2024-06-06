#
# General variables
#
CC := gcc

# Source files (use find only if necessary, see note below)
SRCS := $(shell find ./src -type f -name "*.c")  # Search for .c files in ./src

# Object files (derived from source files)
OBJS := $(SRCS:.c=.o)

# Include directory
INCLUDES := -I./include

# Output executable name
OUTPUT := main

# C compiler flags
CFLAGS := -W -Wall -Werror -Wextra -Wpedantic

#
# Release build settings
#

RELDIR := build
RELOUT := $(RELDIR)/$(OUTPUT)
RELOBJS := $(addprefix $(RELDIR)/,$(OBJS))  # Add build directory prefix to object files
RELCFLAGS := -O0 -DNDEBUG

#
# Debug build settings
#

DBGDIR := debug
DBGOUT := $(DBGDIR)/$(OUTPUT)
DBGOBJS := $(addprefix $(DBGDIR)/,$(OBJS))  # Add debug directory prefix to object files
DGGCFLAGS := -g -O0 -DDEBUG

.PHONY: clean prep debug build remake

# Build target (depends on prep and prog)
build: prep prog

# Debug target (depends on prep and prep_debug)
debug: prep prep_debug

# Default target to build both debug and release versions (can be customized)
all: debug build

#
# Debug rules
#
prep_debug: $(DBGOUT)  # Ensure debug directory exists

$(DBGOUT): $(DBGOBJS)
	$(CC) $(CFLAGS) $(DBGCFLAGS) $(INCLUDES) -o $(DBGOUT) $^ 

$(DBGDIR)/%.o: %.c  # Compile source files from ./src
	$(CC) -c $(CFLAGS) $(DBGCFLAGS) $(INCLUDES) -o $@ $<

#
# Release rules
#
prog: $(RELOUT)

$(RELOUT): $(RELOBJS) # Include directory dependency
	$(CC) $(CFLAGS) $(RELCFLAGS) $(INCLUDES) -o $(RELOUT) $^

$(RELDIR)/%.o: %.c  # Compile source files from ./src
	$(CC) -c $(CFLAGS) $(RELCFLAGS) $(INCLUDES) -o $@ $<

#
# Utilities
#
remake: clean all

prep:
	@mkdir -p $(DBGDIR) $(RELDIR) $(DBGDIR)/src $(RELDIR)/src # Create build directories

clean:
	rm -rf $(RELOUT) $(RELOBJS) $(DBGOUT) $(DBGOBJS)
