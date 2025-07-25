/**
 * @file main.cpp
 * @brief Main entry point for the unofficial-fan-videogame-baseball-club game.
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-23
 *
 * @copyright Copyright (C) 2025 Eeshvar Das (Erik Douglas Ward)
 *
 * @license SPDX-License-Identifier: AGPL-3.0-or-later
 *
 * This program is free software: you can redistribute it and/or modify
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
#include "scheduling/league_scheduler_2.h" // Includes the LeagueSchedulerNS namespace
#include "scheduling/team_data.h"       // For Team struct
#include "scheduling/player_data.h"     // For Player struct [26]
#include "scheduling/game_data.h"       // For Game and ResidencyBlock structs [9]

// Using the new namespace explicitly
using namespace LeagueSchedulerNS;

int main() {
    std::cout << "Starting APMW League Schedule Generation (C++ 3.5.0 with Money & Players)" << std::endl;

    // Initialize the 18 teams with cities and mascot/fan theme placeholders [17, 27]
    // Note: Official team names are omitted as per C++ 3.5.0 directive for this version [26, 27]
    std::vector<Team> all_teams;

    // Atlantic Union (9 teams)
    // Keystone Region
    all_teams.push_back({"Maine", "Lumberjack Spirit", UnionType::ATLANTIC_UNION, RegionType::KEYSTONE, {}});
    all_teams.push_back({"New York", "Metropolitan Spirit", UnionType::ATLANTIC_UNION, RegionType::KEYSTONE, {}});
    all_teams.push_back({"Philadelphia", "Founder Spirit", UnionType::ATLANTIC_UNION, RegionType::KEYSTONE, {}});
    all_teams.push_back({"Pittsburgh", "Iron Spirit", UnionType::ATLANTIC_UNION, RegionType::KEYSTONE, {}});
    // Tidewater Region
    all_teams.push_back({"Atlanta", "Peach Blossom", UnionType::ATLANTIC_UNION, RegionType::TIDEWATER, {}});
    all_teams.push_back({"Miami", "Manatee Calm", UnionType::ATLANTIC_UNION, RegionType::TIDEWATER, {}});
    all_teams.push_back({"Charlotte", "Aviator Grit", UnionType::ATLANTIC_UNION, RegionType::TIDEWATER, {}});
    // The Confluence
    all_teams.push_back({"Cleveland", "Guardian Resolve", UnionType::ATLANTIC_UNION, RegionType::CONFLUENCE, {}});
    all_teams.push_back({"Detroit", "Automaker Drive", UnionType::ATLANTIC_UNION, RegionType::CONFLUENCE, {}});

    // Pacific Union (9 teams)
    // Golden Pennant
    all_teams.push_back({"Los Angeles", "Star Radiance", UnionType::PACIFIC_UNION, RegionType::GOLDEN_PENNANT, {}});
    all_teams.push_back({"San Diego", "Surf Vibe", UnionType::PACIFIC_UNION, RegionType::GOLDEN_PENNANT, {}});
    all_teams.push_back({"San Francisco", "Seal Endurance", UnionType::PACIFIC_UNION, RegionType::GOLDEN_PENNANT, {}});
    // Cascade Territory
    all_teams.push_back({"Seattle", "Rainier Force", UnionType::PACIFIC_UNION, RegionType::CASCADE_TERRITORY, {}});
    // The Sunstone Division
    all_teams.push_back({"Austin", "Armadillo Resilience", UnionType::PACIFIC_UNION, RegionType::SUNSTONE_DIVISION, {}});
    all_teams.push_back({"Dallas", "Lonestar Pride", UnionType::PACIFIC_UNION, RegionType::SUNSTONE_DIVISION, {}});
    all_teams.push_back({"Denver", "Summit Peak", UnionType::PACIFIC_UNION, RegionType::SUNSTONE_DIVISION, {}});
    // The Heartland Core
    all_teams.push_back({"St. Louis", "Archer Aim", UnionType::PACIFIC_UNION, RegionType::HEARTLAND_CORE, {}});
    all_teams.push_back({"Kansas City", "Monarch Reign", UnionType::PACIFIC_UNION, RegionType::HEARTLAND_CORE, {}});

    // Populate teams with some players, including "star players" [17, 27]
    // Player data structures with financial values [26, 27]
    for (auto& team : all_teams) {
        team.roster.push_back({"PlayerA_" + team.city, 85, 1.5, 5000000, 10000000, false});
        team.roster.push_back({"PlayerB_" + team.city, 80, 1.2, 3000000, 5000000, false});
        team.roster.push_back({"PlayerC_" + team.city, 75, 1.0, 2000000, 3000000, false});
        // Add a star player to some teams for demonstration
        if (team.city == "Los Angeles" || team.city == "New York" || team.city == "Austin") {
            team.roster.push_back({"StarPlayer_" + team.city, 95, 2.0, 15000000, 25000000, true}); // [17, 26]
        } else {
            team.roster.push_back({"PlayerD_" + team.city, 70, 0.8, 1000000, 2000000, false});
        }
    }

    LeagueScheduler2 scheduler;
    int games_per_team = 110; // APMW lore recommends 110-120 games [8, 27]

    std::vector<ResidencyBlock> season_schedule = scheduler.generateSeasonSchedule(all_teams, games_per_team);

    std::cout << "\n--- Sample Season Schedule ---" << std::endl;
    for (const auto& block : season_schedule) {
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "Residency Block: " << block.host_team.city << " Host "
                  << (block.is_apex_residency ? "(APEX RESIDENCY)" : "") << std::endl; // NEW: Indicate Apex Residency
        std::cout << "  Visiting Residents: ";
        for (const auto& visitor : block.visiting_residents) {
            std::cout << visitor.city << " ";
        }
        std::cout << std::endl;
        std::cout << "  Dates: " << block.start_date << " to " << block.end_date << std::endl;
        std::cout << "  Games (" << block.games.size() << "):" << std::endl;
        for (const auto& game : block.games) {
            std::cout << "    - " << game.date << ": "
                      << game.team1.city << " (Away/First Bat) vs. "
                      << game.team2.city << " (Home/Second Bat) "
                      << " at " << game.actual_host_stadium.city << " Stadium. Type: ";
            if (game.game_type == GameType::REGULAR_SEASON) {
                std::cout << "REGULAR_SEASON";
            } else if (game.game_type == GameType::CROSSROADS_GAME) {
                std::cout << "CROSSROADS_GAME";
            } else if (game.game_type == GameType::APEX_RESIDENCY_GAME) { // NEW GameType display
                std::cout << "APEX_RESIDENCY_GAME";
            }
            std::cout << std::endl;
        }
    }

    std::cout << "\nSchedule generation complete." << std::endl;

    return 0;
}
