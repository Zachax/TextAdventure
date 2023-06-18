#include "item.h"

Item::Item(const std::string& name, const std::string& description, bool movable) : 
    name(name), description(description), movable(movable) {}

const std::string& Item::GetName() const {
    return name;
}

const std::string& Item::GetDescription() const {
    return description;
}

bool Item::IsMovable() const {
    return movable;
}