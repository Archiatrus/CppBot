#pragma once

#include "sc2api/sc2_interfaces.h"
#include "sc2api/sc2_agent.h"
#include "sc2api/sc2_map_info.h"
#include "sc2lib/sc2_lib.h"


class CppBot : public sc2::Agent
{
public:
    CppBot();
    virtual void OnStep() override;
    virtual void OnGameEnd() override;
};

