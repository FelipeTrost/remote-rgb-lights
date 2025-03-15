cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Fetch ArduinoFake repository
FetchContent_Declare(
  ArduinoFake
  GIT_REPOSITORY https://github.com/FabioBatSilva/ArduinoFake.git
  GIT_TAG master
)
FetchContent_MakeAvailable(ArduinoFake)

# Include ArduinoFake headers
include_directories(${ArduinoFake_SOURCE_DIR}/src)

# Add ArduinoFakeLib as a static library
file(GLOB_RECURSE ARDUINO_FAKE_SRC ${ArduinoFake_SOURCE_DIR}/src/*.cpp)
add_library(ArduinoFakeLib STATIC ${ARDUINO_FAKE_SRC})

target_include_directories(ArduinoFakeLib PUBLIC ${ArduinoFake_SOURCE_DIR}/src)

# Add test executable for patterns_test
add_executable(patterns_test
  tests/patterns_test.cpp
  tests/mock.cpp
  rgb-lights/LedPatterns.cpp
)

# Link GoogleTest and ArduinoFakeLib to patterns_test
target_link_libraries(
  patterns_test
  GTest::gtest_main
  ArduinoFakeLib
)

# Discover tests in patterns_test
include(GoogleTest)
gtest_discover_tests(patterns_test)

# Add test executable for parser_test
add_executable(parser_test
  tests/url-parser.cpp
  rgb-lights/url-parser.cpp
)

# Link GoogleTest and ArduinoFakeLib to parser_test
target_link_libraries(
  parser_test
  GTest::gtest_main
  ArduinoFakeLib
)

# Discover tests in parser_test
gtest_discover_tests(parser_test)
