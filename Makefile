
TITLE = "Pocha's Game Engine"
VERSION = "v0.1.0"

PLATFORM := all

ifeq ($(PLATFORM), all)
all:
	make PLATFORM=gnu+linux
	make PLATFORM=mingw
install:
	make install DIR_INSTALL=$(DIR_INSTALL) PLATFORM=gnu+linux
	make install DIR_INSTALL=$(DIR_INSTALL) PLATFORM=mingw
uninstall:
	make uninstall DIR_INSTALL=$(DIR_INSTALL) PLATFORM=gnu+linux
	make uninstall DIR_INSTALL=$(DIR_INSTALL) PLATFORM=mingw
clean:
	make clean PLATFORM=gnu+linux
	make clean PLATFORM=mingw	
else
ifeq ($(PLATFORM), gnu+linux)
	DIR_INC = /usr/include
	DIR_LIB = /usr/lib
	DIR_BIN = /usr/bin
	CC := cc
else
ifeq ($(PLATFORM), mingw)
	DIR_INC = /usr/x86_64-w64-mingw32/include
	DIR_LIB = /usr/x86_64-w64-mingw32/lib
	DIR_BIN = /usr/x86_64-w64-mingw32/bin
	CC := x86_64-w64-mingw32-cc
else
all: $(error platform `$(PLATFORM)` not supported)
endif
endif

DIR_INSTALL_INC = $(DIR_INSTALL)$(DIR_INC)
DIR_INSTALL_LIB = $(DIR_INSTALL)$(DIR_LIB)
DIR_INSTALL_BIN = $(DIR_INSTALL)$(DIR_BIN)
DIR_OBJ = obj-$(PLATFORM)

DIRS = $(DIR_INSTALL_INC)/pge/ \
       $(DIR_INSTALL_LIB)/pge/ \
       $(DIR_INSTALL_BIN)/

DIRS_SRC = $(shell find src -type d)
DIRS_OBJ = $(DIRS_SRC:src/%=$(DIR_OBJ)/%/)
SRC = $(shell find src -name '*.c')
OBJ = $(SRC:src/%.c=$(DIR_OBJ)/%.o)

C_FLAGS = -O3

LIB = $(DIR_LIB)/pul/{str,put,vec}.o

%/:
	mkdir -p $@

$(DIR_OBJ)/%.o: src/%.c
	$(CC) $< -o $@ -c $(C_FLAGS)

all: $(DIRS_OBJ) $(OBJ)

install: all uninstall $(DIRS)
	cp -ru inc/* $(DIR_INSTALL_INC)/pge
	cp -ru $(DIR_OBJ)/* $(DIR_INSTALL_LIB)/pge
	cp -u bin/pge $(DIR_INSTALL_BIN)/

uninstall:
	rm -rf $(DIR_INSTALL_INC)/pge/
	rm -rf $(DIR_INSTALL_LIB)/pge/
	rm -f $(DIR_INSTALL_BIN)/pge

clean:
	rm -rf $(DIR_OBJ)

endif

