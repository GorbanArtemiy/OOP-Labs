cmake_minimum_required(VERSION 3.10)
project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include)

# Добавляем исходные файлы
set(SOURCES
    src/Point.cpp
    src/Figure.cpp
    src/Rectangle.cpp
    src/Triangle.cpp
    src/Square.cpp
    main.cpp
)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME}_main ${SOURCES})

# Добавление тестов
enable_testing()

# Создание библиотек проекта
add_library(${PROJECT_NAME}_Point_lib src/Point.cpp)
add_library(${PROJECT_NAME}_Figure_lib src/Figure.cpp)
add_library(${PROJECT_NAME}_Rectangle_lib src/Rectangle.cpp)
add_library(${PROJECT_NAME}_Square_lib src/Square.cpp)
add_library(${PROJECT_NAME}_Triangle_lib src/Triangle.cpp)

# Общие зависимости для всех тестов
set(common_libs gtest_main ${PROJECT_NAME}_Point_lib ${PROJECT_NAME}_Figure_lib)

# Тесты для Point
add_executable(test_${PROJECT_NAME}_Point tests/Point_unit.cpp)
target_link_libraries(test_${PROJECT_NAME}_Point PRIVATE gtest_main ${PROJECT_NAME}_Point_lib)

# Тесты для Figure
add_executable(test_${PROJECT_NAME}_Figure tests/Figure_unit.cpp)
target_link_libraries(test_${PROJECT_NAME}_Figure PRIVATE ${common_libs})

# Тесты для Rectangle
add_executable(test_${PROJECT_NAME}_Rectangle tests/Rectangle_unit.cpp)
target_link_libraries(test_${PROJECT_NAME}_Rectangle PRIVATE ${common_libs} ${PROJECT_NAME}_Rectangle_lib)

# Тесты для Triangle
add_executable(test_${PROJECT_NAME}_Triangle tests/Triangle_unit.cpp)
target_link_libraries(test_${PROJECT_NAME}_Triangle PRIVATE ${common_libs} ${PROJECT_NAME}_Triangle_lib)

# Тесты для Square
add_executable(test_${PROJECT_NAME}_Square tests/Square_unit.cpp)
target_link_libraries(test_${PROJECT_NAME}_Square PRIVATE ${common_libs} ${PROJECT_NAME}_Square_lib)

# Общий тест
add_executable(test_${PROJECT_NAME}_General tests/General_unit.cpp)
target_link_libraries(test_${PROJECT_NAME}_General PRIVATE ${common_libs})
target_link_libraries(test_${PROJECT_NAME}_General PRIVATE ${common_libs} ${PROJECT_NAME}_Rectangle_lib)
target_link_libraries(test_${PROJECT_NAME}_General PRIVATE ${common_libs} ${PROJECT_NAME}_Square_lib)
target_link_libraries(test_${PROJECT_NAME}_General PRIVATE ${common_libs} ${PROJECT_NAME}_Triangle_lib)

# Добавление тестов в тестовый набор
include(GoogleTest)
gtest_discover_tests(test_${PROJECT_NAME}_Point)
gtest_discover_tests(test_${PROJECT_NAME}_Figure)
gtest_discover_tests(test_${PROJECT_NAME}_Rectangle)
gtest_discover_tests(test_${PROJECT_NAME}_Triangle)
gtest_discover_tests(test_${PROJECT_NAME}_Square)
gtest_discover_tests(test_${PROJECT_NAME}_General)