# CMakeList.txt: проект CMake для calc_with_dll; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.10)

# unar opers
add_subdirectory("arcsin")
add_subdirectory("arccos")
add_subdirectory("sinus")
add_subdirectory("cosin")
add_subdirectory("ln")

# binary opers
add_subdirectory("power")
add_subdirectory("mod")
