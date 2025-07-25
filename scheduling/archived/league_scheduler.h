#ifndef LEAGUE_SCHEDULER_H
#define LEAGUE_SCHEDULER_H

#include <vector>
#include <string>
#include <map>
#include <memory> // For std::shared_ptr

#include "game_data.h" // Includes Team and Game definitions

// The LeagueScheduler class, managed by the League Agent [21-28]
class LeagueScheduler {
public:
    // Constructor
    LeagueScheduler(const std::vector<std::shared_ptr<Team>>& all_teams);

    // Main function to generate the entire season schedule [21-26, 28]
    std::vector<ResidencyBlock> generateSeasonSchedule(int num_games_per_team);

private:
    std::vector<std::shared_ptr<Team>> teams_; // All 18 teams in the league [30]

    // Helper to create a single residency block, including host vs. residents and Crossroads games
    ResidencyBlock createResidencyBlock(
        std::shared_ptr<Team> host,
        const std::vector<std::shared_ptr<Team>>& visitors,
        const std::string& current_date,
        int block_duration_days
    );

    // Helper to generate Crossroads Games with alternating first bat rule [13, 14, 18-20]
    std::vector<Game> generateCrossroadsGames(
        std::shared_ptr<Team> visiting_team1,
        std::shared_ptr<Team> visiting_team2,
        std::shared_ptr<Team> actual_host_stadium_team, // The team hosting the entire residency
        const std::string& current_date,
        int num_games_in_series
    );

    // Helper to advance date
    std::string advanceDate(const std::string& current_date, int days);

    // Helper to find teams by Union/Region (for internal games)
    std::vector<std::shared_ptr<Team>> getTeamsInRegion(RegionType region);
    std::vector<std::shared_ptr<Team>> getTeamsInUnion(UnionType union_type);

    // Note: In a real implementation, you'd have more sophisticated methods for:
    // - Allocating teams to residency blocks
    // - Ensuring balance in schedules (e.g., number of home/away games, strength of schedule)
    // - Handling special rivalry games like "Heartland-Confluence Series" or "Coast-to-Coast Showdowns" [40]
    // - Managing game dates and series lengths
};

#endif // LEAGUE_SCHEDULER_H
