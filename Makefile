
MAYOR = 0
MINOR = 3
PATCH = 0

PLATFORM := gnu+linux

ifeq ($(PLATFORM), gnu+linux)
	INC_DIR = /usr/include
	LIB_DIR = /usr/lib
	CC := cc
else
ifeq ($(PLATFORM), mingw)
	INC_DIR = /usr/x86_64-w64-mingw32/include
	LIB_DIR = /usr/x86_64-w64-mingw32/lib
	CC := x86_64-w64-mingw32-cc
else
all: $(error platform `$(PLATFORM)` not supported)
endif
endif

INSTALL_INC_DIR = $(INSTALL_DIR)$(INC_DIR)
INSTALL_LIB_DIR = $(INSTALL_DIR)$(LIB_DIR)
OBJ_DIR = obj-$(PLATFORM)

DIRS = $(INSTALL_INC_DIR)/pge/ \
       $(INSTALL_LIB_DIR)/pge/ \
       $(INSTALL_BIN_DIR)/

SRC_DIRS = $(shell find src -type d)
OBJ_DIRS = $(SRC_DIRS:src/%=$(OBJ_DIR)/%/)
SRC = $(shell find src -type f ! -name version.c)
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

C_FLAGS = -fms-extensions -O3 -Wall

LIB = $(LIB_DIR)/pul/{str,put,vec}.o

%/:
	mkdir -p $@

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $< -o $@ -c $(C_FLAGS)

inc/version.h: src/version.c
	printf "`cat $<`" $(MAYOR) $(MINOR) $(PATCH) > $@

all: inc/version.h $(OBJ_DIRS) $(OBJ)

install: all uninstall $(DIRS)
	cp -ru inc/* $(INSTALL_INC_DIR)/pge
	cp -ru $(OBJ_DIR)/* $(INSTALL_LIB_DIR)/pge

uninstall:
	rm -rf $(INSTALL_INC_DIR)/pge/
	rm -rf $(INSTALL_LIB_DIR)/pge/

clean:
	rm -rf inc/version.h $(OBJ_DIR)

