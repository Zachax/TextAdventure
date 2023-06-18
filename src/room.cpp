#include "room.h"

Room::Room(const string& name, const string& description) : name(name), description(description) {}

// Add an item to a room
void Room::AddItem(Item* item) {
    items.push_back(item);
}

// Add a character to a room
void Room::AddCharacter(Character* character) {
    characters.push_back(character);
}

// Remove an item from a room
void Room::RemoveItem(Item* item) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (*it == item) {
            items.erase(it);
            break;
        }
    }
}

// Remove a character from a room
void Room::RemoveCharacter(Character* character) {
    for (auto it = characters.begin(); it != characters.end(); ++it) {
        if (*it == character) {
            characters.erase(it);
            break;
        }
    }
}

Item* Room::FindItem(const string& itemName) {
    for (auto& item : items) {
        if (item->GetName() == itemName) {
            return item;
        }
    }
    return nullptr; // Not found
}

Character* Room::FindCharacter(const string& characterName) {
    for (auto& character : characters) {
        if (character->GetName() == characterName) {
            return character;
        }
    }
    return nullptr;
}

const string& Room::GetName() const {
    return name;
}

const string& Room::GetDescription() const {
    return description;
}

void Room::PrintDescription() const {
    std::cout << "Room: " << GetName() << std::endl;
    std::cout << "Description: " << GetDescription() << std::endl;
}

void Room::SetDescription(string desc) {
    description = desc;
}

void Room::PrintItems() const {
    if (items.empty()) {
        std::cout << "There are no items in the room." << std::endl;
    }
    else {
        std::cout << "Items in the room:" << std::endl;
        for (const auto& item : items) {
            std::cout << "- " << item->GetName() << std::endl;
        }
    }
}

void Room::PrintCharacters() const {
    if (characters.empty()) {
        std::cout << "There are no characters in the room." << std::endl;
    }
    else {
        std::cout << "Characters in the room:" << std::endl;
        for (const auto& character : characters) {
            std::cout << "- " << character->GetName() << std::endl;
        }
    }
}

// Add a pathway to another room
void Room::AddPathway(Room* destination) {
    pathways.push_back(new Pathway(this, destination));
}