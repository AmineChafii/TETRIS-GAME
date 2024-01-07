CC=gcc
FLAGS=-Wall -pedantic
INC=-Isrc/
CFLAGS=$(FLAGS) -c -g --std=c99 $(INC)
LFLAGS=$(FLAGS) -lncurses
DIR_GUARD=@mkdir -p $(@D)

# Configurations de construction.
CFG=release
ifeq ($(CFG),debug)
FLAGS += -g -DDEBUG -DSMB_DEBUG
endif
ifneq ($(CFG),debug)
ifneq ($(CFG),release)
	@echo "Configuration "$(CFG)" spécifiée invalide."
	@echo "Vous devez spécifier une configuration lors de l'exécution de make, par exemple :"
	@echo "  make CFG=debug"
	@echo "Les choix sont 'release', 'debug'."
	@exit 1
endif
endif

SDL=yes
ifeq ($(SDL),yes)
CFLAGS += `sdl-config --cflags` -DWITH_SDL=1
LFLAGS += `sdl-config --libs` -lSDL_mixer
endif
ifneq ($(SDL),yes)
ifneq ($(SDL),no)
	@echo "Configuration SDL "$(SDL)" spécifiée invalide."
	@echo "Vous devez spécifier la configuration SDL lors de l'exécution de make, par exemple :"
	@echo "  make SDL=yes"
	@echo "Les choix sont 'yes', 'no'."
	@exit 1
endif
endif

# Sources et objets
SOURCES=$(shell find src/ -type f -name "*.c")
OBJECTS=$(patsubst src/%.c,obj/$(CFG)/%.o,$(SOURCES))
DEPS=$(patsubst src/%.c,deps/%.d,$(SOURCES))

# Cibles principales
.PHONY: all clean clean_all

all: bin/$(CFG)/main

GTAGS: $(SOURCES)
	gtags

clean:
	rm -rf obj/$(CFG)/* bin/$(CFG)/* src/*.gch GTAGS GPATH GRTAGS

clean_all:
	rm -rf bin/* obj/* deps/*

# --- Règle de compilation
obj/$(CFG)/%.o: src/%.c
	$(DIR_GUARD)
	$(CC) $(CFLAGS) $< -o $@
	$(CC) $(CFLAGS) -MM $< | sed -e 's~\(.*\)\.o~deps/\1.d obj/$(CFG)/\1.o~' > deps/$(notdir $(basename $<)).d

# --- Règle de liaison
bin/$(CFG)/main: $(OBJECTS)
	$(DIR_GUARD)
	$(CC) $(OBJECTS) $(LFLAGS) -o bin/$(CFG)/main

ifneq "$(MAKECMDGOALS)" "clean_all"
endif
