#ifndef LEAGUE_SCHEDULER_2_H
#define LEAGUE_SCHEDULER_2_H

#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "team_data.h"
#include "game_data.h"

namespace LeagueSchedulerNS {

    class LeagueScheduler2 {
    public:
        // Main function to generate the season schedule [26, 45]
        std::vector<ResidencyBlock> generateSeasonSchedule(const std::vector<Team>& all_teams, int games_per_team);
    
    private:
        // Helper function to create a single residency block [26, 45]
        ResidencyBlock createResidencyBlock(const Team& host, const std::vector<Team>& visitors);
    
        // Implements the "alternating first bat" rule for Crossroads Games [26, 38, 39, 45, 48]
        std::vector<Game> generateCrossroadsGames(const Team& visitor1, const Team& visitor2, const Team& host_stadium, int num_games_in_series);
    
        // Random number generator
        std::mt19937 rng;
    };

}

#endif // LEAGUE_SCHEDULER_2_H
