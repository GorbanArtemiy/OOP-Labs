cmake_minimum_required(VERSION 3.10)
project(lab1)

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

# Создание библиотеки из main.cpp
add_library(${PROJECT_NAME}_lib src/main.cpp)

# Добавление тестов
enable_testing()

# Создание тестового исполняемого файла и связывание его с Google Test и библиотекой проекта
add_executable(test_${PROJECT_NAME} tests/unit.cpp)
target_link_libraries(test_${PROJECT_NAME} PRIVATE gtest_main ${PROJECT_NAME}_lib)

# Добавление тестов в тестовый набор
include(GoogleTest)
gtest_discover_tests(test_${PROJECT_NAME})
