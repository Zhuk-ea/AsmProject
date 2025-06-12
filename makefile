# Компиляторы и флаги
CC = gcc
ASM = nasm
CFLAGS = -m32 -lm -Wall -Wextra
ASMFLAGS = -f elf32
LDFLAGS = -m32

# Имена файлов
ASM_SRC = AsmFunctions.asm
ASM_OBJ = $(ASM_SRC:.asm=.o)
C_SRC = main.c
TARGET = program

# Сборка по умолчанию
all: $(TARGET)

# Линковка C и ассемблерного кода
$(TARGET): $(ASM_OBJ) $(C_SRC)
	$(CC) $(LDFLAGS) $^ -o $@

# Компиляция ассемблерного кода
%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

# Очистка
clean:
	rm -f $(TARGET) *.o

# Запуск программы
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run