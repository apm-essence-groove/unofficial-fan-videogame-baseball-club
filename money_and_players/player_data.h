#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

#include <string>
#include <vector> // Though not directly used by Player struct, often needed for collections of players.

// Structure to represent an individual player
struct Player {
    int player_id;            // Unique identifier for the player
    std::string name;         // Player's full name
    std::string position;     // E.g., "P" (Pitcher), "C" (Catcher), "1B" (First Baseman), "CF" (Center Fielder)
    double skill_rating;      // Overall skill metric for game simulation (e.g., 0.0-100.0) [1]
    double salary;            // Player's annual salary, a key financial attribute [1, 2]
    double market_value;      // Player's estimated market value for trades or contracts [1]
    bool is_star_player;      // True if the player is considered a "star" and subject to agentic control [1, 2]

    // Constructor for easy initialization of Player objects
    Player(int id, const std::string& n, const std::string& pos,
           double skill, double sal, double mv, bool is_star)
        : player_id(id), name(n), position(pos), skill_rating(skill),
          salary(sal), market_value(mv), is_star_player(is_star) {}

    // Note: The direct integration with ADK agents (e.g., storing an agent ID or pointer)
    // would be handled by higher-level logic or specific agent implementations,
    // not necessarily directly within this fundamental data structure.
};

#endif // PLAYER_DATA_H
