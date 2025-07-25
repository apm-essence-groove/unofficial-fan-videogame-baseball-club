#include "league_scheduler_2.h"
#include <iostream>
#include <chrono> // For seeding the random number generator
#include <algorithm> // For std::shuffle
#include <random>    // For std::mt19937 and std::uniform_int_distribution

namespace LeagueSchedulerNS {

// Constructor to initialize the random number generator
LeagueScheduler2::LeagueScheduler2() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {}

std::vector<ResidencyBlock> LeagueScheduler2::generateSeasonSchedule(const std::vector<Team>& all_teams, int games_per_team) {
    std::vector<ResidencyBlock> season_schedule;

    if (all_teams.size() < 3) {
        std::cerr << "Need at least 3 teams to create a residency block (1 host + 2 visitors)." << std::endl;
        return season_schedule;
    }

    // A simplified approach for demonstration:
    // Iterate through teams as potential hosts and create some residency blocks.
    // In a real scenario, this would be a much more sophisticated algorithm
    // ensuring balanced schedules, varied matchups, etc., aiming for 110-120 games per team [4, 17].

    int residency_block_counter = 0;
    for (const auto& host_team : all_teams) {
        std::vector<Team> potential_visitors;
        for (const auto& team : all_teams) {
            if (team.id != host_team.id) {
                potential_visitors.push_back(team);
            }
        }

        if (potential_visitors.size() < 2) {
            // Not enough visitors for this host, skip to the next host
            continue;
        }

        // Shuffle potential visitors and pick the first two for this residency
        std::shuffle(potential_visitors.begin(), potential_visitors.end(), rng);
        std::vector<Team> visiting_teams = {potential_visitors, potential_visitors[18]};

        // Create a residency block
        ResidencyBlock block = createResidencyBlock(host_team, visiting_teams);
        season_schedule.push_back(block);
        residency_block_counter++;

        // For demonstration, let's limit the number of residency blocks.
        // A full season would generate schedules until games_per_team is met [17].
        if (residency_block_counter >= all_teams.size() / 2) { // Example: Half as many residency blocks as teams
            break;
        }
    }

    // Note: This simplified scheduler does not guarantee `games_per_team` for all teams.
    // A robust League Agent would implement complex algorithms to achieve this [15, 19, 20].
    std::cout << "Generated " << season_schedule.size() << " residency blocks." << std::endl;
    return season_schedule;
}

ResidencyBlock LeagueScheduler2::createResidencyBlock(const Team& host, const std::vector<Team>& visitors) {
    ResidencyBlock block;
    block.host_team = host;
    block.visiting_residents = visitors; // This stores the vector of visitors
    block.start_date = "2025-07-01"; // Placeholder
    block.end_date = "2025-07-07";   // Placeholder

    // Ensure there are at least two visitors for Crossroads Games [13]
    if (visitors.size() < 2) {
        std::cerr << "Error: Not enough visiting residents for a residency block and Crossroads Games." << std::endl;
        return block; // Return empty block or handle error
    }

    // Games between Host and Visitors (e.g., 3 games)
    for (int i = 0; i < 3; ++i) {
        Game game;
        game.team1 = visitors; // Corrected: Use specific visitor by index
        game.team2 = host;
        game.designated_home_team_for_batting = host; // Host team bats second
        game.actual_host_stadium = host;
        game.date = block.start_date + " Game " + std::to_string(i + 1);
        game.game_type = GameType::REGULAR_SEASON;
        block.games.push_back(game);
    }

    // Host plays Visitors[18] (e.g., 3 games)
    for (int i = 0; i < 3; ++i) {
        Game game;
        game.team1 = visitors[18]; // Corrected: Use specific visitor by index
        game.team2 = host;
        game.designated_home_team_for_batting = host; // Host team bats second
        game.actual_host_stadium = host;
        game.date = block.start_date + " Game " + std::to_string(i + 4);
        game.game_type = GameType::REGULAR_SEASON;
        block.games.push_back(game);
    }

    // Crossroads Games between visiting residents [5, 21]
    // 5-game series as per lore example [5, 22]
    std::vector<Game> crossroads_series = generateCrossroadsGames(visitors, visitors[18], host, 5); // Corrected: Pass individual Team objects
    block.games.insert(block.games.end(), crossroads_series.begin(), crossroads_series.end());

    return block;
}

std::vector<Game> LeagueScheduler2::generateCrossroadsGames(const Team& visitor1, const Team& visitor2, const Team& host_stadium, int num_games_in_series) {
    std::vector<Game> series_games;

    // Randomly determine who hits first in Game 1 [6, 22]
    std::uniform_int_distribution<> distrib(0, 1);
    bool visitor1_bats_first_in_game1 = (distrib(rng) == 0);

    for (int i = 0; i < num_games_in_series; ++i) {
        Game game;
        game.actual_host_stadium = host_stadium;
        game.game_type = GameType::CROSSROADS_GAME;
        game.date = "Crossroads Game " + std::to_string(i + 1);

        bool current_game_visitor1_bats_first;
        if (num_games_in_series % 2 != 0) { // Odd number of games (e.g., 5-game series) [7, 22]
            current_game_visitor1_bats_first = (i % 2 == 0) ? visitor1_bats_first_in_game1 : !visitor1_bats_first_in_game1;
        } else { // Even number of games (e.g., 4-game series) - logic from source [7]
            current_game_visitor1_bats_first = (i % 2 == 0) ? visitor1_bats_first_in_game1 : !visitor1_bats_first_in_game1;
        }

        if (current_game_visitor1_bats_first) {
            game.team1 = visitor1; // Visitor 1 bats first (away team for batting purposes) [7]
            game.team2 = visitor2; // Visitor 2 bats second (home team for batting purposes) [8]
            game.designated_home_team_for_batting = visitor2;
        } else {
            game.team1 = visitor2; // Visitor 2 bats first
            game.team2 = visitor1; // Visitor 1 bats second
            game.designated_home_team_for_batting = visitor1;
        }
        series_games.push_back(game);
    }
    return series_games;
}

} // namespace LeagueSchedulerNS
