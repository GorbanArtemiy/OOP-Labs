cmake_minimum_required(VERSION 3.10)
project(lab4)

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

# Создаем исполняемый файл
add_executable(${PROJECT_NAME}_main main.cpp)

# Добавление тестов
enable_testing()

# Тесты для Point
add_executable(test_${PROJECT_NAME}_Point tests/Point_unit.cpp)
target_link_libraries(test_${PROJECT_NAME}_Point PRIVATE gtest_main)

# Тесты для Figure
add_executable(test_${PROJECT_NAME}_Figure tests/Figure_unit.cpp)
target_link_libraries(test_${PROJECT_NAME}_Figure PRIVATE gtest_main)

# Тесты для NAngle
add_executable(test_${PROJECT_NAME}_Nangle tests/NAngle_unit.cpp)
target_link_libraries(test_${PROJECT_NAME}_Nangle PRIVATE gtest_main)

# Общий тест
add_executable(test_${PROJECT_NAME}_General tests/General_unit.cpp)
target_link_libraries(test_${PROJECT_NAME}_General PRIVATE gtest_main)

# Добавление тестов в тестовый набор
include(GoogleTest)
gtest_discover_tests(test_${PROJECT_NAME}_Point)
gtest_discover_tests(test_${PROJECT_NAME}_Figure)
gtest_discover_tests(test_${PROJECT_NAME}_Nangle)
gtest_discover_tests(test_${PROJECT_NAME}_General)