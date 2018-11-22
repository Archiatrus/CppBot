#include "CppBot.h"
#include "sc2api/sc2_api.h"


CppBot::CppBot() {}

void CppBot::OnStep()
{
    if (Observation()->GetGameLoop()==0)
    {
            const auto units = Observation()->GetUnits(sc2::Unit::Alliance::Self, sc2::IsUnit(sc2::UNIT_TYPEID::ZERG_DRONE));
            const auto target = Observation()->GetGameInfo().enemy_start_locations.front();
            Actions()->UnitCommand(units,sc2::ABILITY_ID::ATTACK,target);
    }
}

void CppBot::OnGameEnd()
{
        std::cout << "OnGameEnd() was called." << std::endl;
}
