#include "../include/NPCFactory.hpp"
#include "../include/Squirrel.hpp"
#include "../include/Druid.hpp"
#include "../include/Orc.hpp"
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <sstream>

// Инициализация реестра типов NPC
std::unordered_map<std::string, std::function<std::shared_ptr<NPC>(const Point&, bool)>> NPCFactory::InitializeRegistry() {
    std::unordered_map<std::string, std::function<std::shared_ptr<NPC>(const Point&, bool)>> registry;
    registry["Squirrel"] = [](const Point& position, bool is_alive) {
        return std::make_shared<Squirrel>(position, is_alive);
    };
    registry["Orc"] = [](const Point& position, bool is_alive) {
        return std::make_shared<Orc>(position, is_alive);
    };
    registry["Druid"] = [](const Point& position, bool is_alive) {
        return std::make_shared<Druid>(position, is_alive);
    };
    return registry;
}


std::shared_ptr<NPC> NPCFactory::CreateNPC(const std::string& type, const Point& position, bool is_alive) {
    static const auto npc_registry = InitializeRegistry();
    auto it = npc_registry.find(type);
    if (it != npc_registry.end()) {
        return it->second(position, is_alive);
    }
    throw std::invalid_argument("NPC of type \"" + type + "\" is not allowed.");
}


void NPCFactory::DumpNPCToStream(std::ostream& out, const std::shared_ptr<NPC>& npc, bool dump_id) {
    if (!out) {
        throw std::ios_base::failure("Output stream is not valid.");
    }
    out << "NPC";
    if (dump_id) {
        out << "_" << npc->GetId();
    }
    if (!npc->IsAlive()) {
        out << "(dead)";
    }
    out << ":\n";
    out << npc->GetType() << '\n';
    out << npc->GetPosition() << '\n';
}


std::shared_ptr<NPC> NPCFactory::LoadNPCFromStream(std::istream& in) {
    if (!in) {
        throw std::ios_base::failure("Input stream is not valid.");
    }

    std::string line;
    if (!std::getline(in, line) || line.substr(0, 3) != "NPC") {
        throw std::runtime_error("Incorrect format of NPC-file: it must start with \"NPC:\"");
    }

    bool is_alive = true;
    if (line.size() >= 10 && line.find("(dead)") != std::string::npos) {
        is_alive = false;
    }

    std::string npc_type;
    if (!(in >> npc_type)) {
        throw std::runtime_error("Failed to read NPC type.");
    }

    Point position;
    if (!(in >> position)) {
        throw std::runtime_error("Failed to read NPC position.");
    }

    return CreateNPC(npc_type, position, is_alive);
}
