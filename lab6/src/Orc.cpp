#include "../include/Orc.hpp"
#include <iostream>

Orc::Orc(const Point& position, bool is_alive)
  : NPC("Orc", position, is_alive) {}

// Accept
bool Orc::LetsFight(NPC* other) {
    return !other->Defend(this);
}

// Visit
bool Orc::Defend(NPC* other) {
    bool result = this->is_alive_;
    if (other->GetType() == "Squirrel") {
        result = false;
    }

    this->is_alive_ = result;
    return result;
}