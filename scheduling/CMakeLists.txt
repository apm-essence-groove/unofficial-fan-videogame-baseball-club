# Create a library target for all the code in this directory.
# "INTERFACE" is used because this is a header-only library,
# meaning it doesn't produce compiled output.
add_library(scheduling_lib INTERFACE)

# Tell CMake that anyone who uses "scheduling_lib" needs to
# include the current directory to find its header files (e.g., league_scheduler_2.h).
target_include_directories(scheduling_lib
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# This module depends on the money_and_players module because
# LeagueScheduler2 operates on Team and Game objects (which contain Player objects).
# Linking privately ensures its include paths are correctly inherited.
target_link_libraries(scheduling_lib PRIVATE money_and_players_lib)
