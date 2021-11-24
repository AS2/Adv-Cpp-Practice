# CMakeList.txt: проект CMake для engine; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (engine "main.cpp" "def.h" "wrapper/wrapper.h" "engine/engine.h" "tested_classes/testedClasses.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
