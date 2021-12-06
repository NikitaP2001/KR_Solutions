TARGET = mallt

SRC_DIR = .
OBJ_DIR = .
INC_DIR = .

vpath %.c SRC_DIR
vpath %.h INC_DIR
vpath %.o OBJ_DIR

CFLAGS = -std=gnu11 -ffunction-sections -fdata-sections -g0 -O3 -Wall -s -mconsole
LDFLAGS = -Wl,--gc-sections,--strip-all
CC=gcc

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(subst $(SRC_DIR)/,$(OBJ_DIR)/,$(SOURCES:.c=.o))

%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	del $(OBJ_DIR)\*.o
	del $(TARGET).exe
