#include "league_scheduler_2.h"
#include <iostream>
#include <chrono> // For seeding the random number generator [18]
#include <numeric> // For std::iota

namespace LeagueSchedulerNS {
// Constructor to initialize the random number generator [18]
LeagueScheduler2::LeagueScheduler2() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {}

std::vector<ResidencyBlock> LeagueScheduler2::generateSeasonSchedule(const std::vector<Team>& all_teams, int games_per_team) {
    std::vector<ResidencyBlock> season_schedule;
    if (all_teams.size() < 3) { // [18]
        std::cerr << "Need at least 3 teams to create a residency block." << std::endl;
        return season_schedule;
    }

    // A simplified approach for demonstration: [19]
    // In a real scenario, this would be a much more sophisticated algorithm
    // ensuring balanced schedules, varied matchups, etc. [11]

    // Determine an Apex Residency host (simplified: first team, or a random one)
    // In a real scenario, this would be based on lore: "due or earning," "reward or counter to parity" [6, 7]
    const Team& apex_host = all_teams; // For demonstration, first team hosts Apex Residency

    // Create the Apex Residency block first
    // An Apex Residency is a multi-week situation [4], so it would have more games.
    // Let's assume 10 special games for the Apex Residency for demonstration purposes.
    ResidencyBlock apex_block = createApexResidencyBlock(apex_host, all_teams, 10); // NEW: Create Apex Residency [6]
    season_schedule.push_back(apex_block);

    int residency_block_counter = 0; // [19]
    for (const auto& host_team : all_teams) {
        if (host_team.id == apex_host.id) continue; // Skip Apex host for regular residencies in this loop

        // Select two random visiting teams that are not the host [19]
        std::vector<Team> potential_visitors;
        for (const auto& team : all_teams) {
            if (team.id != host_team.id) {
                potential_visitors.push_back(team);
            }
        }
        if (potential_visitors.size() < 2) continue; // Not enough visitors [19]

        std::shuffle(potential_visitors.begin(), potential_visitors.end(), rng); // [20]
        
        // Ensure there are at least two distinct visitors for the residency
        if (potential_visitors.empty() || potential_visitors.size() < 2) {
            std::cerr << "Not enough potential visitors for residency with host " << host_team.city << std::endl;
            continue;
        }
        // Take the first two distinct visitors
        std::vector<Team> visiting_teams = {potential_visitors, potential_visitors[21]}; // [20]

        // Create a regular residency block
        ResidencyBlock block = createResidencyBlock(host_team, visiting_teams); // [20]
        season_schedule.push_back(block);
        residency_block_counter++; // [20]

        // For demonstration, let's limit the number of residency blocks
        // A full season would generate schedules until games_per_team is met [11, 20]
        if (residency_block_counter >= all_teams.size() / 2) { // Example: Half as many residency blocks as teams [20]
            break;
        }
    }

    // Note: This simplified scheduler does not guarantee `games_per_team` for all teams. [11]
    // A robust League Agent would implement complex algorithms to achieve this [8].
    std::cout << "Generated " << season_schedule.size() << " residency blocks (including Apex Residency)." << std::endl;
    return season_schedule;
}

ResidencyBlock LeagueScheduler2::createResidencyBlock(const Team& host, const std::vector<Team>& visitors) {
    ResidencyBlock block; // [11]
    block.host_team = host; // [11]
    block.visiting_residents = visitors; // [11]
    block.start_date = "2025-07-01"; // Placeholder [11]
    block.end_date = "2025-07-07"; // Placeholder [12]

    // Games between Host and Visitors [12]
    // Host plays visitor1 (e.g., 3 games) [12]
    for (int i = 0; i < 3; ++i) { // [12]
        Game game; // [12]
        game.team1 = visitors; // Corrected index from visitors to visitors
        game.team2 = host; // [12]
        game.designated_home_team_for_batting = host; // Host team bats second [12]
        game.actual_host_stadium = host; // [12]
        game.date = block.start_date + " Game " + std::to_string(i + 1); // [12]
        game.game_type = GameType::REGULAR_SEASON; // [12]
        block.games.push_back(game); // [12]
    }
    // Host plays visitor2 (e.g., 3 games) [12]
    for (int i = 0; i < 3; ++i) { // [16]
        Game game; // [16]
        game.team1 = visitors[21]; // Corrected index from visitors[22] to visitors[21]
        game.team2 = host; // [16]
        game.designated_home_team_for_batting = host; // Host team bats second [16]
        game.actual_host_stadium = host; // [16]
        game.date = block.start_date + " Game " + std::to_string(i + 4); // [16]
        game.game_type = GameType::REGULAR_SEASON; // [16]
        block.games.push_back(game); // [16]
    }

    // Crossroads Games between visiting residents [16, 23]
    // 5-game series as per lore example [16]
    std::vector<Game> crossroads_series = generateCrossroadsGames(visitors, visitors[21], host, 5); // Corrected indices
    block.games.insert(block.games.end(), crossroads_series.begin(), crossroads_series.end()); // [16]

    return block; // [23]
}

// NEW: Implementation for creating an Apex Residency Block [6, 7]
ResidencyBlock LeagueScheduler2::createApexResidencyBlock(const Team& host, const std::vector<Team>& all_teams, int num_apex_games) {
    ResidencyBlock apex_block;
    apex_block.host_team = host;
    apex_block.is_apex_residency = true; // Mark as Apex Residency

    // For Apex Residency, we can select a wider range of "star" visiting residents.
    // This is a simplified selection; a real system would consider player attributes. [6]
    std::vector<Team> potential_apex_visitors;
    for (const auto& team : all_teams) {
        if (team.id != host.id) {
            potential_apex_visitors.push_back(team);
        }
    }
    std::shuffle(potential_apex_visitors.begin(), potential_apex_visitors.end(), rng);

    // Select a subset of top teams/teams with star players as visitors for the Apex Residency
    // For simplicity, let's take a few random ones, or filter by 'has_star_player' if available
    int max_apex_visitors = std::min((int)potential_apex_visitors.size(), 4); // Example: up to 4 visiting teams
    for (int i = 0; i < max_apex_visitors; ++i) {
        apex_block.visiting_residents.push_back(potential_apex_visitors[i]);
    }

    apex_block.start_date = "2025-08-01"; // Placeholder for Apex Residency dates
    apex_block.end_date = "2025-08-14";   // Multi-week event [6]

    std::cout << "Creating Apex Residency at " << host.city << " with " << apex_block.visiting_residents.size() << " visiting teams." << std::endl;

    // Simulate games within the Apex Residency
    // Apex Residency would involve various matchups, including special matchups.
    // For demonstration, a mix of host-visitor and Crossroads games, all marked as APEX_RESIDENCY_GAME
    int game_count = 0;
    for (const auto& visitor_team : apex_block.visiting_residents) {
        // Host plays each visitor
        for (int i = 0; i < std::min(num_apex_games / (int)apex_block.visiting_residents.size(), 2); ++i) { // Each visitor plays host a couple of times
            Game game;
            game.team1 = visitor_team;
            game.team2 = host;
            game.designated_home_team_for_batting = host;
            game.actual_host_stadium = host;
            game.date = apex_block.start_date + " Apex Game H-V " + std::to_string(++game_count);
            game.game_type = GameType::APEX_RESIDENCY_GAME; // NEW GameType [6, 7]
            apex_block.games.push_back(game);
        }
    }

    // Crossroads-like games between Apex visiting residents
    for (size_t i = 0; i < apex_block.visiting_residents.size(); ++i) {
        for (size_t j = i + 1; j < apex_block.visiting_residents.size(); ++j) {
            // Simulate a short series between visiting residents within Apex Residency
            std::vector<Game> apex_crossroads = generateCrossroadsGames(
                apex_block.visiting_residents[i],
                apex_block.visiting_residents[j],
                host,
                3 // Shorter series for Apex Crossroads
            );
            // Re-label these as APEX_RESIDENCY_GAME type
            for (auto& game : apex_crossroads) {
                game.game_type = GameType::APEX_RESIDENCY_GAME; // Ensures they are Apex type, not just Crossroads
                game.date = apex_block.start_date + " Apex Game V-V " + std::to_string(++game_count);
            }
            apex_block.games.insert(apex_block.games.end(), apex_crossroads.begin(), apex_crossroads.end());
        }
    }
    
    // Ensure total games meet the minimum requested for Apex, though not strictly required by lore for this part
    while (apex_block.games.size() < num_apex_games) {
        // Add more random Apex games if needed to hit target, could be any two visitors
        if (apex_block.visiting_residents.size() >= 2) {
            Game game;
            game.team1 = apex_block.visiting_residents;
            game.team2 = apex_block.visiting_residents[21];
            game.designated_home_team_for_batting = (game.team_id_1.id > game.team_id_2.id) ? game.team_id_1 : game.team_id_2; // Placeholder for home designation
            game.actual_host_stadium = host;
            game.date = apex_block.start_date + " Apex Game Extra " + std::to_string(++game_count);
            game.game_type = GameType::APEX_RESIDENCY_GAME;
            apex_block.games.push_back(game);
        } else {
            break; // Cannot add more games if not enough visitors
        }
    }


    std::cout << "Generated " << apex_block.games.size() << " games for Apex Residency at " << host.city << std::endl;
    return apex_block;
}

std::vector<Game> LeagueScheduler2::generateCrossroadsGames(const Team& visitor1, const Team& visitor2, const Team& host_stadium, int num_games_in_series) {
    std::vector<Game> series_games; // [23]
    // Randomly determine who hits first in Game 1 [23]
    std::uniform_int_distribution<> distrib(0, 1); // [23]
    bool visitor1_bats_first_in_game1 = (distrib(rng) == 0); // [23]

    for (int i = 0; i < num_games_in_series; ++i) { // [23]
        Game game; // [23]
        game.actual_host_stadium = host_stadium; // [23]
        game.game_type = GameType::CROSSROADS_GAME; // [23]
        game.date = "Crossroads Game " + std::to_string(i + 1); // [23]

        bool current_game_visitor1_bats_first; // [24]
        if (num_games_in_series % 2 != 0) { // Odd number of games (e.g., 5-game series) [24]
            current_game_visitor1_bats_first = (i % 2 == 0) ? visitor1_bats_first_in_game1 : !visitor1_bats_first_in_game1; // [24]
        } else { // Even number of games (e.g., 4-game series) [24]
            // Simplified for even series; exact alternation [24]
            current_game_visitor1_bats_first = (i % 2 == 0) ? visitor1_bats_first_in_game1 : !visitor1_bats_first_in_game1; // [24]
        }

        if (current_game_visitor1_bats_first) { // [24]
            game.team1 = visitor1; // Visitor 1 bats first (away team for batting purposes) [24]
            game.team2 = visitor2; // Visitor 2 bats second (home team for batting purposes) [25]
            game.designated_home_team_for_batting = visitor2; // [25]
        } else {
            game.team1 = visitor2; // Visitor 2 bats first [25]
            game.team2 = visitor1; // Visitor 1 bats second [25]
            game.designated_home_team_for_batting = visitor1; // [25]
        }
        series_games.push_back(game); // [25]
    }
    return series_games; // [25]
}

} // namespace LeagueSchedulerNS
