# --- Basic Project Setup ---
cmake_minimum_required(VERSION 3.10)
project(MyAPMWProject VERSION 3.5.0 LANGUAGES CXX) # Project version reflects C++ 3.5.0

# --- Compiler and Standard Settings ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Add Modules (Subdirectories) ---
# Tells CMake to process the CMakeLists.txt file in each subdirectory.
# Each subdirectory is expected to create a library target.
message(STATUS "Adding project modules...")
add_subdirectory(data_models)
add_subdirectory(scheduling)

# --- Main Executable ---
# Creates the main executable for your project from its source file(s).
add_executable(main_app src/main.cpp)

# --- Linking ---
# Links the libraries created by the modules to the main executable.
target_link_libraries(main_app PRIVATE
    data_models_lib
    scheduling_lib
)
2. data_models Module CMakeLists.txt (MyAPMWProject/data_models/CMakeLists.txt)
This module will define the fundamental data structures (Player, Team, Game, ResidencyBlock). Since these are primarily header-only definitions, an INTERFACE library is suitable for exposing their include directories.
# Creates an INTERFACE library named 'data_models_lib'.
# An INTERFACE library is typically used for header-only libraries
# or for targets that only provide include directories and link interfaces.
add_library(data_models_lib INTERFACE)

# Exposes the 'include' directory of this module publicly.
# This allows other targets (like scheduling_lib and main_app) that link against this
# library to find its public header files (e.g., using #include "player_data.h").
target_include_directories(data_models_lib INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
3. scheduling Module CMakeLists.txt (MyAPMWProject/scheduling/CMakeLists.txt)
This module encapsulates the core scheduling logic, including the LeagueScheduler2 class and its implementation. It will need to link against data_models_lib because LeagueScheduler2 operates on Team and Game objects.
# Creates a library named 'scheduling_lib' from its source files.
add_library(scheduling_lib src/league_scheduler.cpp)

# Exposes the 'include' directory of this module publicly.
# This allows other targets (like main_app) that link against this
# library to find its public header files (e.g., #include "league_scheduler_2.h").
target_include_directories(scheduling_lib PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Links this library to data_models_lib because the scheduler
# needs to access Team and Game data structures.
target_link_libraries(scheduling_lib PRIVATE data_models_lib)
