#pragma once

#include <memory>
#include <string>
#include <functional>
#include <unordered_map>
#include <iostream>
#include "NPC.hpp"
#include "Point.hpp"

class NPCFactory {
public:
    static std::shared_ptr<NPC> CreateNPC(const std::string& type, const Point& position, bool is_alive = true);
    static void DumpNPCToStream(std::ostream& out, const std::shared_ptr<NPC>& npc, bool dump_id);
    static std::shared_ptr<NPC> LoadNPCFromStream(std::istream& in);

private:
    // Статический метод для инициализации реестра типов NPC
    static std::unordered_map<std::string, std::function<std::shared_ptr<NPC>(const Point&, bool)>> InitializeRegistry();
};
