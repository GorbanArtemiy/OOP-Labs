#pragma once

#include "NPC.hpp"
#include <memory>

class Druid : public NPC {
public:
    Druid(const Point& position, bool is_alive = true);

    // Accept
    bool LetsFight(NPC* other) override;
    // Visit
    bool Defend(NPC* other) override;
};