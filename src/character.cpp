#include "character.h"

Character::Character(const std::string& name, const std::string& description, bool playerControlled) :
    name(name), description(description), playerControlled(playerControlled) {}

const std::string& Character::GetName() const {
    return name;
}

const std::string& Character::GetDescription() const {
    return description;
}

bool Character::IsPlayerControlled() const {
    return playerControlled;
}
