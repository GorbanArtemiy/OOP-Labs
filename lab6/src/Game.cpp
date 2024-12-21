#include "../include/Game.hpp"
#include "../include/NPC.hpp"
#include <iostream>

void Game::AttachObserver(std::shared_ptr<IGameObjectObserver> observer) {
    this->common_observers_.push_back(observer);
    for (auto& i : this->game_objects_) {
        i->AttachObserver(observer);
    }
}

void Game::AddObject(std::shared_ptr<GameObject> object) {
    this->game_objects_.insert(object);
    for (auto& obs : this->common_observers_) {
        object->AttachObserver(obs);
    }
}

void Game::DeleteObject(std::shared_ptr<GameObject> object) {
    this->game_objects_.erase(object);
}

void Game::StartBattle(double distance) {
    for (auto& i : this->game_objects_) {
        std::shared_ptr<NPC> i_npc = std::dynamic_pointer_cast<NPC>(i);
        if (!i_npc) continue;

        for (auto& j : this->game_objects_) {
            if (i == j) continue;

            std::shared_ptr<NPC> j_npc = std::dynamic_pointer_cast<NPC>(j);
            if (!j_npc) continue;
            if (!i_npc->IsAlive() or !j_npc->IsAlive()) continue;
            if ((i_npc->GetPosition() - j_npc->GetPosition()).Length() > distance) continue;

            // Само сражение
            i_npc->LetsFight(j_npc.get());
            j_npc->LetsFight(i_npc.get());

            // Оповещение
            auto make_message = [](std::shared_ptr<NPC> npc_win, std::shared_ptr<NPC> npc_lose){
                std::string name_win = npc_win->GetType() + '_' + std::to_string(npc_win->GetId());
                std::string name_lose = npc_lose->GetType() + '_' + std::to_string(npc_lose->GetId());
                return "NPC " + name_lose + " was defeated by NPC " + name_win;
            };
            if (!i_npc->IsAlive()) {
                i_npc->Notify(make_message(j_npc, i_npc));
            }
            if (!j_npc->IsAlive()) {
                j_npc->Notify(make_message(i_npc, j_npc));
            }
        }
    }
}