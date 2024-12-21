#pragma once

#include "Point.hpp"
#include <utility>
#include <memory>
#include <vector>
#include <GameObjectObservers.hpp>

// Класс игрового объекта

class GameObject {
private:
    static int counter_;
    int id_;
    Point position_;
    std::vector<std::shared_ptr<IGameObjectObserver>> observers_;


public:
    GameObject();
    GameObject(const Point& position);

    int GetId() const;

    Point GetPosition() const;
    void SetPosition(const Point& point);

    void AttachObserver(std::shared_ptr<IGameObjectObserver> obs);
    void Notify(const std::string& message);

    virtual ~GameObject() {}
};
