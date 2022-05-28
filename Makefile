
MAYOR = 0
MINOR = 3
PATCH = 0

PLATFORM := gnu+linux

ifeq ($(PLATFORM), gnu+linux)
	INC_DIR = /usr/include
	LIB_DIR = /usr/lib
	LIB     = libpge.so
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

C_FLAGS = -fms-extensions -O3 -Wall

%/:
	mkdir -p $@

lib/$(LIB): lib/
	$(CC) -shared -fPIC $(SRC) $(C_FLAGS) -o $@

inc/version.h: src/version.c
	printf "`cat $<`" $(MAYOR) $(MINOR) $(PATCH) > $@

all: inc/version.h lib/$(LIB)

install: all uninstall $(INSTALL_INC_DIR)/pge/ $(INSTALL_LIB_DIR)/
	cp -ru inc/* $(INSTALL_INC_DIR)/pge
	cp -ru lib/$(LIB) $(INSTALL_LIB_DIR)/$(LIB)

uninstall:
	rm -rf $(INSTALL_INC_DIR)/pge/
	rm -rf $(INSTALL_LIB_DIR)/$(LIB)

clean:
	rm -rf lib/ inc/version.h

