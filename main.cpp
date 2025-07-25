/**
 * @file main.cpp
 * @brief Main entry point for the unofficial-fan-videogame-baseball-club game.
 * @author  Eeshvar Das (Erik Douglas Ward)
 * @date 2025-Jul-25
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

#include <iostream>
#include <vector>
#include <string>
#include "scheduling/league_scheduler_2.h"    // Includes the LeagueSchedulerNS namespace
#include "money_and_players/game_data.h"      // For Game and ResidencyBlock structs
// Note: team_data.h and player_data.h are included via game_data.h

// Using the new namespace explicitly
using namespace LeagueSchedulerNS;

int main() {
    std::cout << "Starting APMW League Schedule Generation (C++ 3.5.0 with Money & Players)" << std::endl;

    // Initialize the 18 teams with cities and mascot/fan theme placeholders
    std::vector<Team> all_teams;
    int current_team_id = 1;

    // Atlantic Union (9 teams)
    all_teams.emplace_back(current_team_id++, "Maine", "Lumberjack Spirit", UnionType::ATLANTIC, RegionType::KEYSTONE);
    all_teams.emplace_back(current_team_id++, "New York", "Metropolitan Spirit", UnionType::ATLANTIC, RegionType::KEYSTONE);
    all_teams.emplace_back(current_team_id++, "Philadelphia", "Founder Spirit", UnionType::ATLANTIC, RegionType::KEYSTONE);
    all_teams.emplace_back(current_team_id++, "Pittsburgh", "Iron Spirit", UnionType::ATLANTIC, RegionType::KEYSTONE);
    all_teams.emplace_back(current_team_id++, "Atlanta", "Peach Blossom", UnionType::ATLANTIC, RegionType::TIDEWATER);
    all_teams.emplace_back(current_team_id++, "Miami", "Manatee Calm", UnionType::ATLANTIC, RegionType::TIDEWATER);
    all_teams.emplace_back(current_team_id++, "Charlotte", "Aviator Grit", UnionType::ATLANTIC, RegionType::TIDEWATER);
    all_teams.emplace_back(current_team_id++, "Cleveland", "Guardian Resolve", UnionType::ATLANTIC, RegionType::THE_CONFLUENCE);
    all_teams.emplace_back(current_team_id++, "Detroit", "Automaker Drive", UnionType::ATLANTIC, RegionType::THE_CONFLUENCE);

    // Pacific Union (9 teams)
    all_teams.emplace_back(current_team_id++, "Los Angeles", "Star Radiance", UnionType::PACIFIC, RegionType::GOLDEN_PENNANT);
    all_teams.emplace_back(current_team_id++, "San Diego", "Surf Vibe", UnionType::PACIFIC, RegionType::GOLDEN_PENNANT);
    all_teams.emplace_back(current_team_id++, "San Francisco", "Seal Endurance", UnionType::PACIFIC, RegionType::GOLDEN_PENNANT);
    all_teams.emplace_back(current_team_id++, "Seattle", "Rainier Force", UnionType::PACIFIC, RegionType::CASCADE_TERRITORY);
    all_teams.emplace_back(current_team_id++, "Austin", "Armadillo Resilience", UnionType::PACIFIC, RegionType::THE_SUNSTONE_DIVISION);
    all_teams.emplace_back(current_team_id++, "Dallas", "Lonestar Pride", UnionType::PACIFIC, RegionType::THE_SUNSTONE_DIVISION);
    all_teams.emplace_back(current_team_id++, "Denver", "Summit Peak", UnionType::PACIFIC, RegionType::THE_SUNSTONE_DIVISION);
    all_teams.emplace_back(current_team_id++, "St. Louis", "Archer Aim", UnionType::PACIFIC, RegionType::THE_HEARTLAND_CORE);
    all_teams.emplace_back(current_team_id++, "Kansas City", "Monarch Reign", UnionType::PACIFIC, RegionType::THE_HEARTLAND_CORE);

    // Populate teams with some players, including "star players"
    int current_player_id = 1;
    for (auto& team : all_teams) {
        team.players.emplace_back(current_player_id++, "PlayerA_" + team.city, 85.0, 5000000, 10000000, false);
        team.players.emplace_back(current_player_id++, "PlayerB_" + team.city, 80.0, 3000000, 5000000, false);
        team.players.emplace_back(current_player_id++, "PlayerC_" + team.city, 75.0, 2000000, 3000000, false);
        if (team.city == "Los Angeles" || team.city == "New York" || team.city == "Austin") {
            team.players.emplace_back(current_player_id++, "StarPlayer_" + team.city, 95.0, 15000000, 25000000, true);
        } else {
            team.players.emplace_back(current_player_id++, "PlayerD_" + team.city, 70.0, 1000000, 2000000, false);
        }
    }

    LeagueScheduler2 scheduler;
    int games_per_team = 110;

    std::vector<ResidencyBlock> season_schedule = scheduler.generateSeasonSchedule(all_teams, games_per_team);

    std::cout << "\n--- Sample Season Schedule ---" << std::endl;
    for (const auto& block : season_schedule) {
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "Residency Block: " << block.host_team.city << " Host "
                  << (block.is_apex_residency ? "(APEX RESIDENCY)" : "") << std::endl;
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
            } else if (game.game_type == GameType::APEX_RESIDENCY_GAME) {
                std::cout << "APEX_RESIDENCY_GAME";
            }
            std::cout << std::endl;
        }
    }

    std::cout << "\nSchedule generation complete." << std::endl;

    return 0;
}
