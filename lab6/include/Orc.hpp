#pragma once

#include "NPC.hpp"
#include <memory>

class Werewolf : public NPC {
public:
    Werewolf(const Point& position, bool is_alive = true);

    // Accept
    bool LetsFight(NPC* other) override;
    // Visit
    bool Defend(NPC* other) override;
};