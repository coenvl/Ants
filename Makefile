CC=g++
CFLAGS=-O3 -funroll-loops -c -Wall
LDFLAGS=-O2 -lm
SOURCES=Bot.cc MyBot.cc State.cc Ant.cc Antmap.cc Location.cc
OBJDIR=o
OBJECTS=$(addprefix $(OBJDIR)/,$(addsuffix .o, $(basename ${SOURCES})))
EXECUTABLE=MyBot

#Uncomment the following to enable debugging
#CFLAGS+=-g -DDEBUG

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJDIR)/%.o: %.cc *.h | $(OBJDIR)/.d
	$(CC) $(CFLAGS) $< -o $@

.PRECIOUS: %.d

%.d:
	mkdir -p $*
	touch $@

.PHONY: all clean

clean: 
	-rm -rf $(OBJDIR)
	-rm -f ${EXECUTABLE} ${OBJECTS} *.d *~
	-rm -f debug.txt

