CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude

SRCDIR = src
INCDIR = include
BINDIR = bin

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%.o,$(SOURCES))
DEPS := $(wildcard $(INCDIR)/*.h)

EXECUTABLE = played

all: $(BINDIR)/$(EXECUTABLE)

$(BINDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(BINDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

debug: CFLAGS += -g -O0 -DDEBUG
debug: $(BINDIR)/$(EXECUTABLE)

clean:
	rm -rf $(BINDIR)

.PHONY: all clean debug