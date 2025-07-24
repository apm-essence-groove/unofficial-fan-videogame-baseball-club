#include <iostream>
#include <vector>
#include <memory> // For std::shared_ptr

#include "league_scheduler.h"
#include "team_data.h"

int main() {
    // 1. Initialize all 18 teams using cities and mascots/themes (no official names for 3.5.0) [User Query]
    std::vector<std::shared_ptr<Team>> all_teams;
    
    // Atlantic Union (9 teams)
    // Keystone Region [31, 32]
    all_teams.push_back(std::make_shared<Team>("Maine", "Lumberjack Spirit", UnionType::Atlantic, RegionType::Keystone));
    all_teams.push_back(std::make_shared<Team>("New York", "Metropolitan Pulse", UnionType::Atlantic, RegionType::Keystone));
    all_teams.push_back(std::make_shared<Team>("Philadelphia", "Founder's Legacy", UnionType::Atlantic, RegionType::Keystone));
    all_teams.push_back(std::make_shared<Team>("Pittsburgh", "Iron Will", UnionType::Atlantic, RegionType::Keystone));
    
    // Tidewater Region [31, 32]
    all_teams.push_back(std::make_shared<Team>("Atlanta", "Peach Power", UnionType::Atlantic, RegionType::Tidewater));
    all_teams.push_back(std::make_shared<Team>("Miami", "Manatee Calm", UnionType::Atlantic, RegionType::Tidewater));
    all_teams.push_back(std::make_shared<Team>("Charlotte", "Aviator's Edge", UnionType::Atlantic, RegionType::Tidewater));
    
    // The Confluence (integrates former "Crossroads" teams) [31, 33]
    all_teams.push_back(std::make_shared<Team>("Cleveland", "Guardian Might", UnionType::Atlantic, RegionType::Confluence));
    all_teams.push_back(std::make_shared<Team>("Detroit", "Automaker Drive", UnionType::Atlantic, RegionType::Confluence));

    // Pacific Union (9 teams)
    // Golden Pennant [31, 33]
    all_teams.push_back(std::make_shared<Team>("Los Angeles", "Star Power", UnionType::Pacific, RegionType::GoldenPennant));
    all_teams.push_back(std::make_shared<Team>("San Diego", "Surf Spirit", UnionType::Pacific, RegionType::GoldenPennant));
    all_teams.push_back(std::make_shared<Team>("San Francisco", "Seal Strength", UnionType::Pacific, RegionType::GoldenPennant));
    
    // Cascade Territory [31, 33]
    all_teams.push_back(std::make_shared<Team>("Seattle", "Rainier Resolve", UnionType::Pacific, RegionType::CascadeTerritory));
    
    // The Sunstone Division (integrates former "Crossroads" teams) [31, 33]
    all_teams.push_back(std::make_shared<Team>("Austin", "Armadillo Resilience", UnionType::Pacific, RegionType::SunstoneDivision));
    all_teams.push_back(std::make_shared<Team>("Dallas", "Lonestar Pride", UnionType::Pacific, RegionType::SunstoneDivision));
    all_teams.push_back(std::make_shared<Team>("Denver", "Summit Aspirations", UnionType::Pacific, RegionType::SunstoneDivision));
    
    // The Heartland Core (integrates former "Crossroads" teams) [31, 34]
    all_teams.push_back(std::make_shared<Team>("St. Louis", "Archer Accuracy", UnionType::Pacific, RegionType::HeartlandCore));
    all_teams.push_back(std::make_shared<Team>("Kansas City", "Monarch Nobility", UnionType::Pacific, RegionType::HeartlandCore));

    // 2. Create the LeagueScheduler instance
    LeagueScheduler scheduler(all_teams);

    // 3. Generate the season schedule (e.g., aiming for approx. 110-120 games per team) [10]
    std::vector<ResidencyBlock> season_schedule = scheduler.generateSeasonSchedule(115); // Example target games per team

    // 4. Print a summary of the generated schedule (for verification)
    std::cout << "\n--- Season Schedule Summary (C++ 3.5.0, Version 3.5) ---" << std::endl;
    for (const auto& block : season_schedule) {
        std::cout << "\nResidency Block: Host - " << block.host_team->city
                  << ", Visitors - ";
        for (const auto& visitor : block.visiting_residents) {
            std::cout << visitor->city << " ";
        }
        std::cout << "(" << block.start_date << " to " << block.end_date << ")" << std::endl;
        std::cout << "  Games in block (" << block.games_in_block.size() << "):" << std::endl;
        for (const auto& game : block.games_in_block) {
            std::cout << "    - " << game.team1->city << " vs. " << game.team2->city
                      << " (Designated Home: " << game.designated_home_team_for_batting->city
                      << ", Type: " << game.game_type << ")" << std::endl;
        }
    }
    std::cout << "-----------------------------------------------------" << std::endl;

    return 0;
}
