#include <iostream>
#include "include/Game.hpp"
#include "include/NPCFactory.hpp"
#include "include/GameObjectObservers.hpp"
#include <memory>

int main() {
    auto s1 = NPCFactory::CreateNPC("Squirrel", {5, 10});
    auto w1 = NPCFactory::CreateNPC("Werewolf", {6, 11});
    auto d1 = NPCFactory::CreateNPC("Druid", {4, 9});
    auto d2 = NPCFactory::CreateNPC("Druid", {7, 6});
    auto d3 = NPCFactory::CreateNPC("Druid", {5, 6});
    auto d4 = NPCFactory::CreateNPC("Druid", {6.4, 4.9});

    auto log_obs = std::make_shared<LogGameObjectObserver>("./logs/log.txt");
    auto print_obs = std::make_shared<PrintGameObjectObserver>();

    Game game;
    game.AttachObserver(log_obs);
    game.AttachObserver(print_obs);

    game.AddObject(std::move(s1));
    game.AddObject(std::move(w1));
    game.AddObject(std::move(d1));
    game.AddObject(std::move(d2));
    game.AddObject(std::move(d3));
    game.AddObject(std::move(d4));

    game.StartBattle(10);
}