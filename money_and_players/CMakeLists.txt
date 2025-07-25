# Creates an INTERFACE library named 'money_and_players_lib'.
# An INTERFACE library is typically used for header-only libraries
# or for targets that only provide include directories and link interfaces.
# This reflects the renaming of the data_models module [16].
add_library(money_and_players_lib INTERFACE)

# Exposes the 'include' directory of this module publicly.
# This allows other targets (like scheduling_lib and main_app) that link against this
# library to find its public header files (e.g., player_data.h, team_data.h, game_data.h) [8, 9].
target_include_directories(money_and_players_lib INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
