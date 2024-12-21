#pragma once

#include "GameObject.hpp"
#include <string>

class NPC : public GameObject {
protected:
    std::string type_;
    bool is_alive_;

public:
    NPC(const std::string& type, const Point& pos, bool is_alive = true);

    std::string GetType() const;
    bool IsAlive() const;

/*
Класс NPC одновременно visitor и acceptor.  
*/

    // Accept
    virtual bool LetsFight(NPC* other) = 0;
    // Visit
    virtual bool Defend(NPC* other) = 0;
};