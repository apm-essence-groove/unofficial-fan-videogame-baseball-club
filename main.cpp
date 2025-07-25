/**
 * @file main.cpp
 * @brief Main entry point for the unofficial-fan-videogame-baseball-club game.
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-23
 *
 *
 * Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

// main.cpp (Modified for Money and Players branch)
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm> // For std::shuffle
#include <iomanip>   // For std::setw

#include "team_data.h"
#include "game_data.h"
#include "league_scheduler.h"
#include "player_data.h" // Include for Player struct

// Helper to generate a unique player ID
int next_player_id = 1;
Player generateRandomPlayer(const std::string& team_city, bool is_star = false) {
    std::string player_name = "Player_" + std::to_string(next_player_id);
    double skill = 50.0 + (rand() % 500) / 10.0; // 50.0 to 100.0
    long long salary = 500000 + (rand() % 100) * 10000; // Base salary
    long long market_value = salary * (1.0 + (rand() % 50) / 100.0); // Market value

    if (is_star) {
        player_name = "Star_" + team_city + "_" + std::to_string(next_player_id);
        skill = 90.0 + (rand() % 100) / 10.0; // 90.0 to 100.0 for stars
        salary = 10000000 + (rand() % 100) * 1000000; // High salary for stars
        market_value = salary * (2.0 + (rand() % 100) / 100.0); // High market value for stars
    }
    next_player_id++;
    return Player(next_player_id - 1, player_name, skill, salary, market_value, is_star);
}

//BEGIN PROGRESSIVE CONFLICT

// Forward declarations for classes
class Player;
class Team;
class Ball;
class Game;

/**
 * @class Player
 * @brief Represents a single player in the game.
 */
class Player {
public:
    std::string name;
    int skillLevel;

    Player(std::string name, int skillLevel) : name(name), skillLevel(skillLevel) {}

    void swing() {
        std::cout << name << " is swinging the bat!" << std::endl;
    }
};

/**
 * @class Team
 * @brief Represents a team of players.
 */
class Team {
public:
    std::string name;
    std::vector<Player> players;

    Team(std::string name) : name(name) {}

    void addPlayer(const Player& player) {
        players.push_back(player);
    }

    void printRoster() const {
        std::cout << "Roster for " << name << ":" << std::endl;
        for (const auto& player : players) {
            std::cout << " - " << player.name << " (Skill: " << player.skillLevel << ")" << std::endl;
        }
    }
};

/**
 * @class Ball
 * @brief Represents the baseball.
 */
class Ball {
public:
    int x, y, z; // Position of the ball

    Ball() : x(0), y(0), z(0) {}

    void pitch() {
        std::cout << "The ball is pitched!" << std::endl;
        x = 50; // Simulate ball moving towards the batter
    }
};

/**
 * @class Game
 * @brief Manages the overall game state and flow.
 */
class Game {
private:
    Team team1;
    Team team2;
    Ball ball;
    int scoreTeam1;
    int scoreTeam2;
    int currentInning;

public:
    Game(const Team& t1, const Team& t2) : team1(t1), team2(t2), scoreTeam1(0), scoreTeam2(0), currentInning(1) {}

    void startGame() {
        std::cout << "========================================" << std::endl;
        std::cout << "   Welcome to Unofficial Fan Baseball   " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << team1.name << " vs. " << team2.name << std::endl;
        std::cout << "Let's play ball!" << std::endl;
        std::cout << std::endl;

        team1.printRoster();
        std::cout << std::endl;
        team2.printRoster();
        std::cout << std::endl;
    }

    void playInning() {
        std::cout << "--- Inning " << currentInning << " ---" << std::endl;
        // Simple gameplay logic placeholder
        handleAtBat(team1);
        handleAtBat(team2);
        currentInning++;
    }

    void handleAtBat(const Team& battingTeam) {
        std::cout << battingTeam.name << " is now batting." << std::endl;
        Player batter = battingTeam.players[rand() % battingTeam.players.size()];
        std::cout << batter.name << " is at the plate." << std::endl;

        ball.pitch();
        batter.swing();

        // Simulate hit or miss
        if ((rand() % 10) < batter.skillLevel) {
            std::cout << batter.name << " hits the ball!" << std::endl;
            int bases = (rand() % 4) + 1;
            std::cout << "It's a " << bases << "-base hit!" << std::endl;
            if (&battingTeam == &team1) {
                scoreTeam1 += (bases == 4) ? 1 : 0; // Simplified scoring
            } else {
                scoreTeam2 += (bases == 4) ? 1 : 0;
            }
        } else {
            std::cout << batter.name << " strikes out!" << std::endl;
        }
        printScore();
        std::cout << std::endl;
    }

    void printScore() const {
        std::cout << "Score: " << team1.name << " " << scoreTeam1 << " - " << team2.name << " " << scoreTeam2 << std::endl;
    }

    bool isGameOver() const {
        return currentInning > 9;
    }

    void endGame() {
        std::cout << "========================================" << std::endl;
        std::cout << "              Game Over!                " << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "Final Score:" << std::endl;
        printScore();
        if (scoreTeam1 > scoreTeam2) {
            std::cout << team1.name << " wins!" << std::endl;
        } else if (scoreTeam2 > scoreTeam1) {
            std::cout << team2.name << " wins!" << std::endl;
        } else {
            std::cout << "It's a tie!" << std::endl;
        }
    }
};

//END PROGRESSIVE CONFLICT


/**
 * @brief The main function where the game execution begins.
 * @return 0 on successful execution.
 */
int main() {
    std::cout << "Starting APMW Baseball C++ 3.5.0 Simulation Setup..." << std::endl;

    // Initialize the 18 teams as per the 'single source of truth' for the league structure [50, 51]
    // Using cities and mascot/fan theme placeholders for C++ 3.5.0 as requested [24-26]
    std::vector<Team> teams;
    int team_id_counter = 1;

    // Atlantic Union (9 teams)
    teams.push_back(Team(team_id_counter++, "Maine", "Lumberjack Spirit", UnionType::ATLANTIC, RegionType::KEYSTONE));
    teams.push_back(Team(team_id_counter++, "New York", "Metropolitan Pride", UnionType::ATLANTIC, RegionType::KEYSTONE));
    teams.push_back(Team(team_id_counter++, "Philadelphia", "Founder's Legacy", UnionType::ATLANTIC, RegionType::KEYSTONE));
    teams.push_back(Team(team_id_counter++, "Pittsburgh", "Iron Giant Strength", UnionType::ATLANTIC, RegionType::KEYSTONE));
    teams.push_back(Team(team_id_counter++, "Atlanta", "Peach Power", UnionType::ATLANTIC, RegionType::TIDEWATER));
    teams.push_back(Team(team_id_counter++, "Miami", "Manatee Calm", UnionType::ATLANTIC, RegionType::TIDEWATER));
    teams.push_back(Team(team_id_counter++, "Charlotte", "Aviator's Flight", UnionType::ATLANTIC, RegionType::TIDEWATER));
    teams.push_back(Team(team_id_counter++, "Cleveland", "Guardian Spirit", UnionType::ATLANTIC, RegionType::THE_CONFLUENCE));
    teams.push_back(Team(team_id_counter++, "Detroit", "Automaker Drive", UnionType::ATLANTIC, RegionType::THE_CONFLUENCE));

    // Pacific Union (9 teams)
    teams.push_back(Team(team_id_counter++, "Los Angeles", "Star Power", UnionType::PACIFIC, RegionType::GOLDEN_PENNANT));
    teams.push_back(Team(team_id_counter++, "San Diego", "Surf Vibe", UnionType::PACIFIC, RegionType::GOLDEN_PENNANT));
    teams.push_back(Team(team_id_counter++, "San Francisco", "Seal's Wisdom", UnionType::PACIFIC, RegionType::GOLDEN_PENNANT));
    teams.push_back(Team(team_id_counter++, "Seattle", "Rainier Resolve", UnionType::PACIFIC, RegionType::CASCADE_TERRITORY));
    teams.push_back(Team(team_id_counter++, "Austin", "Armadillo Resilience", UnionType::PACIFIC, RegionType::THE_SUNSTONE_DIVISION));
    teams.push_back(Team(team_id_counter++, "Dallas", "Lonestar Spirit", UnionType::PACIFIC, RegionType::THE_SUNSTONE_DIVISION));
    teams.push_back(Team(team_id_counter++, "Denver", "Summit Peak", UnionType::PACIFIC, RegionType::THE_SUNSTONE_DIVISION));
    teams.push_back(Team(team_id_counter++, "St. Louis", "Archer's Aim", UnionType::PACIFIC, RegionType::THE_HEARTLAND_CORE));
    teams.push_back(Team(team_id_counter++, "Kansas City", "Monarch Reign", UnionType::PACIFIC, RegionType::THE_HEARTLAND_CORE));

    std::cout << "Initialized " << teams.size() << " teams." << std::endl;

    // Populate each team with players, including some star players [8, 9]
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed for player generation
    for (auto& team : teams) {
        // Each team has 25 players (example roster size)
        for (int i = 0; i < 25; ++i) {
            // Randomly assign a few star players
            bool is_star = (rand() % 10 == 0); // ~10% chance for a star player
            team.players.push_back(generateRandomPlayer(team.city, is_star));
        }
        std::cout << "  " << team.city << " (" << team.mascot_theme << ") has " << team.players.size() << " players." << std::endl;
        int star_count = 0;
        for(const auto& player : team.players) {
            if (player.is_star_player) {
                star_count++;
                std::cout << "    - Star Player: " << player.name << " (Skill: " << std::fixed << std::setprecision(1) << player.skill_rating
                          << ", Salary: $" << player.salary << ", Market Value: $" << player.market_value << ")" << std::endl;
            }
        }
        if (star_count == 0) {
             std::cout << "    (No star players on this team in this run)" << std::endl;
        }
    }

    LeagueScheduler scheduler;
    // Example: 110-120 games per season recommended for MVP [38-40]
    // The current createResidencyBlock is simplified and won't hit this target accurately,
    // but the function call demonstrates the intent.
    auto season_schedule = scheduler.generateSeasonSchedule(teams, 110);

    // Logic to print the schedule [Conceptual placeholder replacement]
    std::cout << "\n--- Generated Season Schedule ---" << std::endl;
    for (const auto& residency_block : season_schedule) {
        std::cout << "\nResidency Block: Host - " << residency_block.host_team.city << " (" << residency_block.host_team.mascot_theme << ")";
        std::cout << ", Visitors: ";
        for (const auto& visitor : residency_block.visiting_residents) {
            std::cout << visitor.city << " (" << visitor.mascot_theme << ") ";
        }
        std::cout << std::endl;
        std::cout << "  Games in this block (" << residency_block.games.size() << "):" << std::endl;
        for (const auto& game : residency_block.games) {
            std::cout << "    " << game.date << " [" << (game.game_type == GameType::CROSSROADS_GAME ? "CROSSROADS" : "REGULAR") << "]: "
                      << game.team1.city << " vs " << game.team2.city
                      << " (Designated Home: " << game.designated_home_team_for_batting.city << " @ "
                      << game.actual_host_stadium.city << " Stadium)" << std::endl;
        }
    }
    std::cout << "\n--- End of Schedule ---" << std::endl;

    return 0;
}
