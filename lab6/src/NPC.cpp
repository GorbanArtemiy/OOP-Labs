#include "../include/NPC.hpp"

NPC::NPC(const std::string& type, const Point& pos, bool is_alive)
    : GameObject(pos)
    , type_(type)
    , is_alive_(is_alive) {}

std::string NPC::GetType() const {
    return type_;
}

bool NPC::IsAlive() const {
    return this->is_alive_;
}