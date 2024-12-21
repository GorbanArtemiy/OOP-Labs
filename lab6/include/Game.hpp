#pragma once

#include "GameObject.hpp"
#include "GameObjectObservers.hpp"
#include <unordered_set>
#include <memory>
#include <vector>

class Game {
private:
    std::unordered_set<std::shared_ptr<GameObject>> game_objects_;
    std::vector<std::shared_ptr<IGameObjectObserver>> common_observers_;

public:
    void AttachObserver(std::shared_ptr<IGameObjectObserver> observer);

    void AddObject(std::shared_ptr<GameObject> object);
    void DeleteObject(std::shared_ptr<GameObject> object);

    void StartBattle(double distance);
};
