cmake_minimum_required(VERSION 3.12)
project(inbrain)

add_executable(inbrain interpreter.cpp)

set_target_properties(
  inbrain
  PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
)

