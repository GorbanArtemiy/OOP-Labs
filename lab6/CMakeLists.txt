cmake_minimum_required(VERSION 3.10)
project(lab6)

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

# Создание исполняемого файла
add_executable(${PROJECT_NAME}_exe src/main.cpp)

# Связывание исполняемого файла с библиотеками (если нужно)
# target_link_libraries(lab6_exe PRIVATE ${CMAKE_PROJECT_NAME}_lib)

# Добавление тестов
enable_testing()

add_executable(test_${PROJECT_NAME} tests/unit.cpp)
target_link_libraries(test_${PROJECT_NAME} gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME TestLab6 COMMAND tests)