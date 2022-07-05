
define VERSION_H

# define LIBPACA_VERSION_MAYOR 0
# define LIBPACA_VERSION_MINOR 5
# define LIBPACA_VERSION_PATCH 0

/*
	libpaca
	Copyright (c) 2022 Piero Rojas
	GNU General Public License v3.0
*/

endef

export VERSION_H

PLATFORM := gnu+linux

ifeq ($(PLATFORM),gnu+linux)
PREFIX := $(if $(PREFIX),$(PREFIX),/usr)
INC_DIR = $(PREFIX)/include
LIB_DIR = $(PREFIX)/lib
TARGET  = libpaca.a
else
ifeq ($(PLATFORM), mingw)
PREFIX := $(if $(PREFIX),$(PREFIX),/usr/x86_64-w64-mingw32)
INC_DIR = $(PREFIX)/include
LIB_DIR = $(PREFIX)/lib
TARGET  = libpaca.dll
CC     := x86_64-w64-mingw32-cc
else
all: $(error platform `$(PLATFORM)` not supported)
endif
endif

INSTALL_INC_DIR = $(INSTALL_DIR)$(INC_DIR)
INSTALL_LIB_DIR = $(INSTALL_DIR)$(LIB_DIR)

SRC = $(shell find src -type f ! -name version.c)
OBJ = $(SRC:src/%.c=lib/%.o)

C_FLAGS = -O3 -Wall -Wextra -pedantic -g3

all: inc/version.h lib/$(TARGET)

inc/version.h:
	echo "$$VERSION_H" > $@

lib/%.o: src/%.c
	@mkdir -p $(shell dirname $@)
	$(CC) $< -c -o $@ $(C_FLAGS)

lib/$(TARGET): $(OBJ)
	$(AR) rcs $@ $(OBJ)
	strip -g $@

install: all uninstall
	@mkdir -p $(INSTALL_INC_DIR)/paca/
	@mkdir -p $(INSTALL_LIB_DIR)/
	cp -ru inc/* $(INSTALL_INC_DIR)/paca
	cp -ru lib/$(TARGET) $(INSTALL_LIB_DIR)/$(TARGET)

uninstall:
	rm -rf $(INSTALL_INC_DIR)/paca/
	rm -rf $(INSTALL_LIB_DIR)/$(TARGET)

clean:
	rm -rf lib/ inc/version.h

