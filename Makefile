CC = g++
RM = rm

PROJECT = example.out
HEADERS = picolog.hpp
SOURCES = example.cpp
OBJECTS = $(subst .cpp,.o,$(SOURCES))

CFLAGS = -I. -Wall -Wpedantic

all: $(PROJECT)

$(PROJECT): $(OBJECTS)
	$(CC) -o $(PROJECT) $(OBJECTS) $(CFLAGS)

$(OBJECTS): $(SOURCES) $(HEADERS)
	$(CC) -c $(SOURCES) $(CFLAGS)

clean:
	$(RM) $(OBJECTS)
	$(RM) $(PROJECT)

.PHONY: clean all
