# CMakeList.txt: проект CMake для calc_with_dll; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)             # Стандарт C++
set(CMAKE_CXX_STANDARD_REQUIRED ON)    # Обязательность установки указанного стандарта (если OFF (по умолчанию), то воспринимается как совет)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (calc_with_dll "calc_with_dll.cpp" "calc_with_dll.h" "scanner/scanner.cpp"  "parser/parser.h" "parser/parser.cpp" "operators/operator.h"  "operators/standart_operators.h" "error/error.h" "calculator/calculator.cpp" "calculator/calculator.h"  "token/token.h" "scanner/scanner.h" "eval/eval.cpp" "eval/eval.h")

add_subdirectory("DLLs Code")
