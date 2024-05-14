CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
DEBUG_FLAGS = -g
RELEASE_FLAGS = -O3

SRCDIR = src
INCDIR = include
BINDIR = bin
DEBUG_BINDIR = $(BINDIR)/debug
RELEASE_BINDIR = $(BINDIR)/release

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=%.o)

.DEFAULT_GOAL := release

release: CFLAGS += $(RELEASE_FLAGS)
release: $(RELEASE_BINDIR)/your_program

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(DEBUG_BINDIR)/your_program

clean:
	rm -rf $(BINDIR)/*.o $(DEBUG_BINDIR)/*.o $(RELEASE_BINDIR)/*.o

$(DEBUG_BINDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

$(RELEASE_BINDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

$(DEBUG_BINDIR)/your_program: $(addprefix $(DEBUG_BINDIR)/,$(OBJS))
	$(CC) -o $@ $^ $(CFLAGS)

$(RELEASE_BINDIR)/your_program: $(addprefix $(RELEASE_BINDIR)/,$(OBJS))
	$(CC) -o $@ $^ $(CFLAGS)
