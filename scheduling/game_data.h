/**
 * @file game_data.h
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

#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <string>
#include <vector>
#include <memory> // For std::shared_ptr if managing dynamically allocated Team objects

#include "team_data.h" // Include Team definition

// Represents a single game
struct Game {
    std::shared_ptr<Team> team1; // Using shared_ptr for shared ownership of Team objects
    std::shared_ptr<Team> team2;
    std::shared_ptr<Team> designated_home_team_for_batting; // For Crossroads Games' alternating bat rule [13, 14, 18-20]
    std::shared_ptr<Team> actual_host_stadium; // The team hosting the residency, if applicable [3-9]
    std::string date; // Format: YYYY-MM-DD
    std::string game_type; // e.g., "Regular Season", "Crossroads Game", "Heartland-Confluence Series" [15, 40]

    // Constructor
    Game(std::shared_ptr<Team> t1, std::shared_ptr<Team> t2, std::shared_ptr<Team> designated_home, std::shared_ptr<Team> host_stadium, std::string d, std::string type)
        : team1(t1), team2(t2), designated_home_team_for_batting(designated_home), actual_host_stadium(host_stadium), date(d), game_type(type) {}
};

// Represents a Residency Block [3-9]
struct ResidencyBlock {
    std::shared_ptr<Team> host_team; // One team acts as the Host [3-9]
    std::vector<std::shared_ptr<Team>> visiting_residents; // Two or more other teams are Visiting Residents [3-9]
    std::vector<Game> games_in_block; // All games played during this residency
    std::string start_date;
    std::string end_date;

    // Constructor
    ResidencyBlock(std::shared_ptr<Team> host, const std::vector<std::shared_ptr<Team>>& visitors, std::string start, std::string end)
        : host_team(host), visiting_residents(visitors), start_date(start), end_date(end) {}
};

#endif // GAME_DATA_H
