/**
 * @file league_scheduler.cpp
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

#include "league_scheduler.h"
#include <iostream>
#include <algorithm> // For std::shuffle
#include <random>    // For std::default_random_engine
#include <chrono>    // For std::chrono::system_clock

// For simplicity, we'll use a basic date advancing (not full calendar logic)
// In a real application, a robust date library would be used.
std::string LeagueScheduler::advanceDate(const std::string& current_date, int days) {
    // Placeholder for actual date calculation.
    // This would parse current_date, add days, and format back to string.
    // For now, let's just append days for conceptual understanding.
    // This is NOT production-ready date logic.
    return "2025-XX-" + std::to_string(std::stoi(current_date.substr(8,2)) + days); // Very basic example
}

LeagueScheduler::LeagueScheduler(const std::vector<std::shared_ptr<Team>>& all_teams)
    : teams_(all_teams) {
    // Basic validation: ensure there are 18 teams as per lore [29, 30, 41, 42]
    if (teams_.size() != 18) {
        std::cerr << "Warning: Expected 18 teams for APMW league, but received " << teams_.size() << " teams." << std::endl;
    }
}

std::vector<ResidencyBlock> LeagueScheduler::generateSeasonSchedule(int num_games_per_team) {
    std::vector<ResidencyBlock> season_schedule;
    std::string current_date = "2025-07-23"; // Start date as per your request

    // Example simplified scheduling loop: This would be much more complex in a real League Agent.
    // It would involve balancing travel, matchups, and adhering to the 110-120 game target.
    int total_games_scheduled = 0;
    const int max_season_games = num_games_per_team * 18 / 2; // Roughly, for 18 teams

    // Simple example: Create a few residency blocks.
    // In reality, the League Agent intelligently selects hosts and visitors.
    if (teams_.size() >= 3) {
        // Example 1: Los Angeles hosts New York and Atlanta [4, 6-8, 13-15]
        std::shared_ptr<Team> la_host = nullptr;
        std::shared_ptr<Team> ny_visitor = nullptr;
        std::shared_ptr<Team> atl_visitor = nullptr;

        for (const auto& team : teams_) {
            if (team->city == "Los Angeles") la_host = team;
            if (team->city == "New York") ny_visitor = team;
            if (team->city == "Atlanta") atl_visitor = team;
        }

        if (la_host && ny_visitor && atl_visitor) {
            ResidencyBlock block1 = createResidencyBlock(la_host, {ny_visitor, atl_visitor}, current_date, 7); // 7-day block
            season_schedule.push_back(block1);
            total_games_scheduled += block1.games_in_block.size();
            current_date = advanceDate(current_date, 7);
        }

        // Example 2: More complex scheduling logic would follow here
        // ... (e.g., iterating through regions, ensuring all teams get host/visitor opportunities)
    }

    std::cout << "Generated " << total_games_scheduled << " games for the season." << std::endl;
    return season_schedule;
}

ResidencyBlock LeagueScheduler::createResidencyBlock(
    std::shared_ptr<Team> host,
    const std::vector<std::shared_ptr<Team>>& visitors,
    const std::string& current_date,
    int block_duration_days
) {
    ResidencyBlock block(host, visitors, current_date, advanceDate(current_date, block_duration_days));
    std::cout << "Creating Residency Block hosted by " << host->city << " from " << current_date << " for " << block_duration_days << " days." << std::endl;

    // Host plays all visiting residents
    for (const auto& visitor : visitors) {
        // Assume a 3-game series for simplicity (host vs. visitor)
        for (int i = 0; i < 3; ++i) {
            // Host is always "home" in their own stadium for these games
            block.games_in_block.emplace_back(host, visitor, host, host, current_date, "Regular Season");
            std::cout << " - Game: " << visitor->city << " @ " << host->city << std::endl;
        }
    }

    // Visiting residents play each other (Crossroads Games) [4, 6-8, 13-15]
    if (visitors.size() >= 2) {
        // All pairs of visiting residents play Crossroads Games
        for (size_t i = 0; i < visitors.size(); ++i) {
            for (size_t j = i + 1; j < visitors.size(); ++j) {
                std::shared_ptr<Team> v1 = visitors[i];
                std::shared_ptr<Team> v2 = visitors[j];
                // Assume a 5-game series for Crossroads Games [13, 14, 18-20]
                std::vector<Game> crossroads_series = generateCrossroadsGames(v1, v2, host, current_date, 5);
                block.games_in_block.insert(block.games_in_block.end(), crossroads_series.begin(), crossroads_series.end());
            }
        }
    }

    return block;
}

std::vector<Game> LeagueScheduler::generateCrossroadsGames(
    std::shared_ptr<Team> visiting_team1,
    std::shared_ptr<Team> visiting_team2,
    std::shared_ptr<Team> actual_host_stadium_team,
    const std::string& current_date,
    int num_games_in_series
) {
    std::vector<Game> series_games;
    std::cout << "  - Generating Crossroads Series: " << visiting_team1->city << " vs. " << visiting_team2->city << " at " << actual_host_stadium_team->city << std::endl;

    // Randomly determine who bats first in Game 1 [13, 14, 18-20]
    std::shared_ptr<Team> team_a = visiting_team1;
    std::shared_ptr<Team> team_b = visiting_team2;

    // Use a random device for better randomness
    std::random_device rd;
    std::mt19937 g(rd());
    bool team_a_hits_first_in_game1 = (g() % 2 == 0); // Randomly true or false

    for (int i = 0; i < num_games_in_series; ++i) {
        std::shared_ptr<Team> designated_home_team;
        std::shared_ptr<Team> batting_first_team;

        // Alternate who hits first [13, 14, 18-20]
        // Example: If Team A hits first in Game 1, Team B hits first in Game 2, etc.
        if ((team_a_hits_first_in_game1 && (i % 2 == 0)) || (!team_a_hits_first_in_game1 && (i % 2 != 0))) {
            batting_first_team = team_a;
            designated_home_team = team_b; // Team B bats second (home)
        } else {
            batting_first_team = team_b;
            designated_home_team = team_a; // Team A bats second (home)
        }
        
        // Ensure the game object reflects who is Team1 and Team2 consistently or randomly,
        // but the crucial part is designated_home_team_for_batting.
        series_games.emplace_back(batting_first_team, designated_home_team, designated_home_team, actual_host_stadium_team, current_date, "Crossroads Game");
        std::cout << "    - Game " << (i + 1) << ": " << batting_first_team->city << " (Away) vs. " << designated_home_team->city << " (Designated Home)" << std::endl;
    }
    return series_games;
}

std::vector<std::shared_ptr<Team>> LeagueScheduler::getTeamsInRegion(RegionType region) {
    std::vector<std::shared_ptr<Team>> result;
    for (const auto& team : teams_) {
        if (team->region_type == region) {
            result.push_back(team);
        }
    }
    return result;
}

std::vector<std::shared_ptr<Team>> LeagueScheduler::getTeamsInUnion(UnionType union_type) {
    std::vector<std::shared_ptr<Team>> result;
    for (const auto& team : teams_) {
        if (team->union_type == union_type) {
            result.push_back(team);
        }
    }
    return result;
}
