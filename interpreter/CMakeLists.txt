cmake_minimum_required(VERSION 3.12)
project(inbrain)

add_executable(inbrain interpreter.cpp command.cpp main.cpp data_it.hpp interpreter_error.hpp)

set_target_properties(
  inbrain
  PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
)

