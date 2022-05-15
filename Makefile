
TITLE = "Pocha's Game Engine"
VERSION = "v0.1.0"

PLATFORM := gnu+linux

ifeq ($(PLATFORM), gnu+linux)
	INC_DIR = /usr/include
	LIB_DIR = /usr/lib
	BIN_DIR = /usr/bin
	CC := cc
else
ifeq ($(PLATFORM), mingw)
	INC_DIR = /usr/x86_64-w64-mingw32/include
	LIB_DIR = /usr/x86_64-w64-mingw32/lib
	BIN_DIR = /usr/x86_64-w64-mingw32/bin
	CC := x86_64-w64-mingw32-cc
else
all: $(error platform `$(PLATFORM)` not supported)
endif
endif

INSTALL_INC_DIR = $(INSTALL_DIR)$(INC_DIR)
INSTALL_LIB_DIR = $(INSTALL_DIR)$(LIB_DIR)
INSTALL_BIN_DIR = $(INSTALL_DIR)$(BIN_DIR)
OBJ_DIR = obj-$(PLATFORM)

DIRS = $(INSTALL_INC_DIR)/pge/ \
       $(INSTALL_LIB_DIR)/pge/ \
       $(INSTALL_BIN_DIR)/

SRC_DIRS = $(shell find src -type d)
OBJ_DIRS = $(SRC_DIRS:src/%=$(OBJ_DIR)/%/)
SRC = $(shell find src -name '*.c')
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

C_FLAGS = -O3 -Wall

LIB = $(LIB_DIR)/pul/{str,put,vec}.o

%/:
	mkdir -p $@

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $< -o $@ -c $(C_FLAGS)

all: $(OBJ_DIRS) $(OBJ)

install: all uninstall $(DIRS)
	cp -ru inc/* $(INSTALL_INC_DIR)/pge
	cp -ru $(OBJ_DIR)/* $(INSTALL_LIB_DIR)/pge
	cp -u bin/pge $(INSTALL_BIN_DIR)/

uninstall:
	rm -rf $(INSTALL_INC_DIR)/pge/
	rm -rf $(INSTALL_LIB_DIR)/pge/
	rm -f $(INSTALL_BIN_DIR)/pge

clean:
	rm -rf $(OBJ_DIR)

