# --- Basic Project Setup ---
cmake_minimum_required(VERSION 3.10)
project(MyAPMWProject VERSION 3.5.0 LANGUAGES CXX) # Project version reflects C++ 3.5.0 [18]

# --- Compiler and Standard Settings ---
set(CMAKE_CXX_STANDARD 17) # As per previous setup [19]
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Add Modules (Subdirectories) ---
# Tells CMake to process the CMakeLists.txt file in each subdirectory.
# Each subdirectory is expected to create a library target.
message(STATUS "Adding project modules...")
# Renamed from 'data_models' to 'money_and_players' [16]
add_subdirectory(money_and_players) 
add_subdirectory(scheduling)

# --- Main Executable ---
# Creates the main executable for your project from its source file(s).
# Assumed main.cpp is at the project root [5, 7]
add_executable(main_app main.cpp) 

# --- Linking ---
# Links the libraries created by the modules to the main executable.
target_link_libraries(main_app PRIVATE
    money_and_players_lib # Updated library name
    scheduling_lib
)
