cmake_minimum_required(VERSION 3.20)

project(cpp_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
if(CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES 
      ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

add_subdirectory(src/helloWorld)
add_subdirectory(src/yourName)
add_subdirectory(src/whileString)
add_subdirectory(src/ifAndSwitch)
add_subdirectory(src/whileForFunction)
add_subdirectory(src/simpleVector)
add_subdirectory(src/simpleError)
add_subdirectory(src/calculator)
add_subdirectory(src/asReference)
