#include "../include/Werewolf.hpp"
#include <iostream>

Werewolf::Werewolf(const Point& position, bool is_alive)
  : NPC("Werewolf", position, is_alive) {}

// Accept
bool Werewolf::LetsFight(NPC* other) {
    return !other->Defend(this);
}

// Visit
bool Werewolf::Defend(NPC* other) {
    bool result = this->is_alive_;
    if (other->GetType() == "Squirrel") {
        result = false;
    }

    this->is_alive_ = result;
    return result;
}