
MAYOR = 0
MINOR = 3
PATCH = 0

PLATFORM := gnu+linux

ifeq ($(PLATFORM), gnu+linux)
	INC_DIR = /usr/include
	LIB_DIR = /usr/lib
	LIB     = libpge.a
	CC     := cc
else
ifeq ($(PLATFORM), mingw)
	INC_DIR = /usr/x86_64-w64-mingw32/include
	LIB_DIR = /usr/x86_64-w64-mingw32/lib
	LIB     = libpge.dll
	CC     := x86_64-w64-mingw32-cc
else
all: $(error platform `$(PLATFORM)` not supported)
endif
endif

INSTALL_INC_DIR = $(INSTALL_DIR)$(INC_DIR)
INSTALL_LIB_DIR = $(INSTALL_DIR)$(LIB_DIR)

DIRS = $(INSTALL_INC_DIR)/pge/ \
       $(INSTALL_LIB_DIR)/

SRC = $(shell find src -type f ! -name version.c)
OBJ = $(SRC:src/%.c=lib/%.o)
SRC_DIRS = $(shell find src -type d)
OBJ_DIRS = lib/ $(SRC_DIRS:src%=lib%/)

C_FLAGS = -O3 -Wall -pedantic

all: inc/version.h $(OBJ_DIRS) lib/$(LIB)

%/:
	mkdir -p $@

lib/%.o: src/%.c
	$(CC) $< -c -o $@ $(C_FLAGS)

lib/$(LIB): $(OBJ)
	ar rcs $@ $(OBJ)

inc/version.h: src/version.c
	printf "`cat $<`" $(MAYOR) $(MINOR) $(PATCH) > $@

install: all uninstall $(INSTALL_INC_DIR)/pge/ $(INSTALL_LIB_DIR)/
	cp -ru inc/* $(INSTALL_INC_DIR)/pge
	cp -ru lib/$(LIB) $(INSTALL_LIB_DIR)/$(LIB)

uninstall:
	rm -rf $(INSTALL_INC_DIR)/pge/
	rm -rf $(INSTALL_LIB_DIR)/$(LIB)

clean:
	rm -rf lib/ inc/version.h

