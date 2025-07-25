/**
 * @file team_data.h
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

#ifndef TEAM_DATA_H
#define TEAM_DATA_H

#include <string>
#include <vector>
#include <map>

// Forward declarations to avoid circular dependencies if needed later
class Team;
class Game;
class ResidencyBlock;

// Define Unions and Regions as per APMW lore [12, 31, 36, 37]
enum class UnionType {
    Atlantic, // Atlantic Union [12, 31, 36, 38]
    Pacific   // Pacific Union [12, 21, 31, 37]
};

enum class RegionType {
    // Atlantic Union Regions [31, 37]
    Keystone,    // Northeast Corridor [12, 31, 37]
    Tidewater,   // Southeast [12, 31, 37]
    Confluence,  // Great Lakes industrial heartland, integrates former "Crossroads" teams [17, 31, 37, 39]

    // Pacific Union Regions [31, 39]
    GoldenPennant,  // California, formerly "Sunset Circuit" [12, 31, 39]
    CascadeTerritory, // Pacific Northwest [12, 31, 39]
    SunstoneDivision, // Texas, integrates former "Crossroads" teams [17, 31, 39]
    HeartlandCore   // Deeply rooted in American identity, integrates former "Crossroads" teams [17, 31, 39]
};

// Simplified Team structure for C++ 3.5.0 as per your directive:
// No official team name defined yet, but cities are okay, and using mascots/fan themes.
struct Team {
    std::string city;         // e.g., "Maine", "New York", "Austin" [31-33]
    std::string mascot_theme; // Placeholder for mascot or fan theme (e.g., "Lumberjack Theme", "Armadillo Fanbase")
    UnionType union_type;
    RegionType region_type;
    // Add other team-related data as needed for simulation, but no 'official_name' string for now.

    // Constructor for easier initialization
    Team(std::string city_name, std::string theme, UnionType u_type, RegionType r_type)
        : city(city_name), mascot_theme(theme), union_type(u_type), region_type(r_type) {}
};

#endif // TEAM_DATA_H
