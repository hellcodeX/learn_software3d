TARGET = renderer
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# -lmingw32 -lSDL2main в таком порядке позволяет избежать ошибки <undefined reference to 'WinMain'>
# lm - математическая библиотека
LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lm

PREF_SRC = ./src/
PREF_OBJ = ./obj/

SRC = $(wildcard $(PREF_SRC)*.c)
OBJ = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRC))

.PHONY: all clean run

$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

$(PREF_OBJ)%.o : $(PREF_SRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(TARGET).exe  $(PREF_OBJ)*.o

# @ - turn off out
run:
	@./$(TARGET).exe