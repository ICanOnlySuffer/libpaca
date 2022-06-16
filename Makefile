
MAYOR = 0
MINOR = 4
PATCH = 0

PLATFORM := gnu+linux

ifeq ($(PLATFORM), gnu+linux)
	INC_DIR = /usr/include
	LIB_DIR = /usr/lib
	TARGET  = libpaca.a
	CC     := cc
else
ifeq ($(PLATFORM), mingw)
	INC_DIR = /usr/x86_64-w64-mingw32/include
	LIB_DIR = /usr/x86_64-w64-mingw32/lib
	TARGET  = libpaca.dll
	CC     := x86_64-w64-mingw32-cc
else
all: $(error platform `$(PLATFORM)` not supported)
endif
endif

INSTALL_INC_DIR = $(INSTALL_DIR)$(INC_DIR)
INSTALL_LIB_DIR = $(INSTALL_DIR)$(LIB_DIR)

DIRS = $(INSTALL_INC_DIR)/paca/ \
       $(INSTALL_LIB_DIR)/

SRC = $(shell find src -type f ! -name version.c)
OBJ = $(SRC:src/%.c=lib/%.o)

C_FLAGS = -O3 -Wall -Wextra -pedantic -g3

all: inc/version.h lib/$(TARGET)

lib/%.o: src/%.c
	@mkdir -p $(shell dirname $@)
	$(CC) $< -c -o $@ $(C_FLAGS)

lib/$(TARGET): $(OBJ)
	ar rcs $@ $(OBJ)

inc/version.h: src/version.c
	printf "`cat $<`" $(MAYOR) $(MINOR) $(PATCH) > $@

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

