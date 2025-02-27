# Компиляторы
CC = gcc
CXX = g++

# Флаги компиляции
CFLAGS = -Wall -Wextra -std=c99
CXXFLAGS = -Wall -Wextra -std=c++11

# Дополнительные флаги для C++
LDFLAGS = -lgtest -lpthread

# Исходные файлы
SRC = src/main.c
OBJ = $(SRC:.c=.o)
TEST_SRC = tests/unit/test_main.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)

# Исполняемые файлы
EXECUTABLES = app.exe unit-tests.exe

# Цель all
all: $(EXECUTABLES)

# Цель app.exe
app.exe: $(OBJ)
    $(CC) $(CFLAGS) -o $@ $^

# Цель unit-tests.exe
unit-tests.exe: $(TEST_OBJ)
    $(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Цель clean
clean:
    rm -f $(EXECUTABLES) *.o build/*

# Цель run-int
run-int: app.exe
    ./app.exe

# Цель run-float
run-float: app.exe
    ./app.exe --float

# Цель run-unit-test
run-unit-test: unit-tests.exe
    ./unit-tests.exe

# Цель venv (дополнительно)
venv:
    python3 -m venv venv
    venv/bin/pip install pytest

# Цель run-integration-tests (дополнительно)
run-integration-tests: venv
    venv/bin/pytest tests/integration/
