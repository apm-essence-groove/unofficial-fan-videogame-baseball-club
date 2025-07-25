#ifndef LEAGUE_SCHEDULER_2_H
#define LEAGUE_SCHEDULER_2_H

#include <vector>
#include <string>
#include <random>    // For std::mt19937
#include <algorithm> // For std::shuffle

#include "team_data.h" // Team objects now contain Player objects [23]
#include "game_data.h" // Defines Game and ResidencyBlock structures [24]

namespace LeagueSchedulerNS {

class LeagueScheduler2 {
public:
    // Constructor to initialize the random number generator
    LeagueScheduler2();

    // Main function to generate the season schedule [11]
    std::vector<ResidencyBlock> generateSeasonSchedule(const std::vector<Team>& all_teams, int games_per_team);

private:
    // Helper function to create a single residency block [25]
    ResidencyBlock createResidencyBlock(const Team& host, const std::vector<Team>& visitors);

    // Implements the "alternating first bat" rule for Crossroads Games [5, 6, 22, 25]
    std::vector<Game> generateCrossroadsGames(const Team& visitor1, const Team& visitor2, const Team& host_stadium, int num_games_in_series);

    // Random number generator
    std::mt19937 rng;
};

} // namespace LeagueSchedulerNS

#endif // LEAGUE_SCHEDULER_2_H
