# Компиляторы и флаги
CC = gcc -m32 -no-pie -fno-pie
ASM = nasm
CFLAGS = -m32 -lm -Wall -Wextra
ASMFLAGS = -f elf32
LDFLAGS = -m32
LDLIBS = -lm

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

.PHONY: all

integral: main.c AsmFunctions.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
AsmFunctions.o: AsmFunctions.asm
	nasm -f elf32 $< -o $@

test:
	./integral -R 4:5:1.0:3.0:0.00001:2.0
	./integral -R 4:6:0.0:1.0:0.00001:0.501468
	./integral -R 5:6:1.0:4.0:0.00001:0.240557
	./integral -I 4:1.0:5.0:0.00001:16.0
	./integral -I 5:1.0:5.0:0.00001:37.333
	./integral -I 6:1.0:5.0:0.00001:1089654.7623

