# MyAPMWProject/scheduling/CMakeLists.txt
add_library(scheduling_lib
    scheduling/league_scheduler.cpp # Source file for the scheduler logic
)

# Expose the include directory for scheduling_lib's headers.
target_include_directories(scheduling_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} # Public for scheduler's own headers
)

# Link scheduling_lib to money_and_players_lib because it uses Team/Player objects.
# This automatically brings in the include paths from money_and_players_lib.
target_link_libraries(scheduling_lib PRIVATE
    money_and_players_lib
)
