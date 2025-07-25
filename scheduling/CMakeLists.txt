# Creates a library named 'scheduling_lib' from its source files [20].
add_library(scheduling_lib src/league_scheduler.cpp)

# Exposes the 'include' directory of this module publicly.
# This allows other targets (like main_app) that link against this
# library to find its public header files (e.g., league_scheduler_2.h) [14, 20].
target_include_directories(scheduling_lib PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Links this library to money_and_players_lib because the scheduler
# needs to access Team and Game data structures [20, 21].
target_link_libraries(scheduling_lib PRIVATE money_and_players_lib)
