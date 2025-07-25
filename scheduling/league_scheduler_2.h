#ifndef LEAGUE_SCHEDULER_2_H
#define LEAGUE_SCHEDULER_2_H

#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "team_data.h" // Includes Team structure, which now contains Player objects [1, 9, 10]
#include "game_data.h" // Includes Game and ResidencyBlock structures [1, 8, 11]

namespace LeagueSchedulerNS { // New namespace for organization and to prevent naming collisions [12, 13]

class LeagueScheduler2 {
public:
    // Main function to generate the season schedule
    // It operates on Team objects that explicitly contain Player objects [10, 14]
    std::vector<ResidencyBlock> generateSeasonSchedule(const std::vector<Team>& all_teams, int games_per_team);

private:
    // Helper function to create a single residency block
    ResidencyBlock createResidencyBlock(const Team& host, const std::vector<Team>& visitors);

    // Implements the "alternating first bat" rule for Crossroads Games [10, 15, 16]
    std::vector<Game> generateCrossroadsGames(const Team& visitor1, const Team& visitor2, const Team& host_stadium, int num_games_in_series);

    // Random number generator
    std::mt19937 rng;
};

} // namespace LeagueSchedulerNS

#endif // LEAGUE_SCHEDULER_2_H
