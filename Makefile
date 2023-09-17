CC = gcc
INC_DIR = include
LIB_DIR = lib
SRC_DIR	= src
BUILD_DIR = build

DEBUG ?= 1

ifeq ($(DEBUG), 1)
	OCFLAGS = -g

else
	OCFLAGS = -Ofast -mwindows
endif

CFLAGS = -Wall -Werror -Wextra -Wpedantic -I$(INC_DIR) -L$(LIB_DIR) $(OCFLAGS)
LDFLAGS = -lmingw32 -lSDL2main -lSDL2

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

TARGET = card_game.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.depend: $(SRC)
	$(CC) $(CFLAGS) -MM $^ > $@
	powershell.exe -Command "(Get-Content -Raw $@) -replace '(\w+)\.o', '$(BUILD_DIR)/$$1.o' | Set-Content $@"
	powershell.exe -Command "(Get-Content -Raw $@) -replace '(\S+\.o).*?(\S+\.c)(.|\n)*?[^\\](\r\n)', \"`$$0`t`$$(CC) `$$(CFLAGS) -c -o `$$1 `$$2`r`n\" | Set-Content $@"

include .depend

clean:
	del /s $(TARGET) *.o