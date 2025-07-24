/**
 * @file main.cpp
 * @brief Main entry point for the unofficial-fan-videogame-baseball-club game.
 * @author Your Name
 * @date 2025-07-23
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

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

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

/**
 * @brief The main function where the game execution begins.
 * @return 0 on successful execution.
 */
int main() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Create teams
    Team homeTeam("Mesa Solar Sox");
    Team awayTeam("Peoria Javelinas");

    // Add players to teams
    homeTeam.addPlayer(Player("Ace Pitcher", 8));
    homeTeam.addPlayer(Player("Slugger Sam", 7));
    homeTeam.addPlayer(Player("Speedy Pete", 6));

    awayTeam.addPlayer(Player("Curveball King", 8));
    awayTeam.addPlayer(Player("Homerun Harry", 7));
    awayTeam.addPlayer(Player("Golden Glove Gary", 6));

    // Create and start the game
    Game baseballGame(homeTeam, awayTeam);
    baseballGame.startGame();

    // Main game loop
    while (!baseballGame.isGameOver()) {
        baseballGame.playInning();
    }

    // End the game
    baseballGame.endGame();

    return 0;
}
