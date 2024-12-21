#include "../include/Druid.hpp"
#include <iostream>

Druid::Druid(const Point& position, bool is_alive)
  : NPC("Druid", position, is_alive) {}

// Accept
bool Druid::LetsFight(NPC* other) {
    return !other->Defend(this);
}

// Visit
bool Druid::Defend(NPC* other) {
    bool result = this->is_alive_;
    if (other->GetType() == "Orc") {
        result = false;
    }
    
    this->is_alive_ = result;
    return result;
}