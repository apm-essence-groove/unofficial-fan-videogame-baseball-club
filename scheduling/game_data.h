#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <string>
#include <vector>
#include "team_data.h" // Include Team structure

// Enum to categorize different types of games
enum class GameType {
    REGULAR_SEASON,
    CROSSROADS_GAME, // Special games between visiting residents at a host's stadium [38, 39, 46, 47]
    PLAYOFF_GAME,
    ALL_STAR,
    UNKNOWN
};

// Represents a single game matchup
struct Game {
    Team team1;
    Team team2;
    Team designated_home_team_for_batting; // Crucial for "alternating first bat" rule in Crossroads Games [26, 38, 39, 45, 48]
    Team actual_host_stadium; // The team whose stadium the game is played at [26, 45]
    std::string date;         // Date of the game (e.g., "YYYY-MM-DD")
    GameType game_type;

    Game() : game_type(GameType::UNKNOWN) {}
};

// Represents a residency block, where multiple teams gather at a host stadium
struct ResidencyBlock {
    Team host_team;
    std::vector<Team> visiting_residents;
    std::vector<Game> games; // All games played within this residency [26, 45]
    std::string start_date;
    std::string end_date;

    ResidencyBlock() {}
};

#endif // GAME_DATA_H
