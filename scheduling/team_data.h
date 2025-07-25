// team_data.h (Modified for Money and Players branch)
#ifndef TEAM_DATA_H
#define TEAM_DATA_H

#include <string>
#include <vector>          // Required for std::vector
#include "player_data.h"   // NEW: Include the new player data structure

// Enum for Union types, reflecting the league's organizational structure [5, 6]
enum class UnionType {
    Atlantic,
    Pacific
};

// Enum for Region types within Unions, deepening the lore [5, 6]
enum class RegionType {
    Keystone, Tidewater, TheConfluence, // Atlantic Union regions
    GoldenPennant, CascadeTerritory, TheSunstoneDivision, TheHeartlandCore // Pacific Union regions
};

// Structure to represent a baseball team
struct Team {
    std::string city;
    // For C++ 3.5.0, official team names are intentionally excluded;
    // using mascot/fan theme as a placeholder [5-8].
    std::string mascot_theme;
    UnionType union_type;
    RegionType region_type;
    std::vector<Player> players; // NEW: Holds the team's roster of individual players [1, 3]

    // Constructor for easy initialization of Team objects
    Team(const std::string& c, const std::string& mt, UnionType ut, RegionType rt)
        : city(c), mascot_theme(mt), union_type(ut), region_type(rt) {}

    // Method to add a player to the team's roster
    void add_player(const Player& p) {
        players.push_back(p);
    }
};

#endif // TEAM_DATA_H
