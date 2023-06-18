#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <iostream>

#include "item.h"
#include "character.h"
#include "pathway.h"

using string = std::string;

// Forward declarations
class Item;
class Character;
class Pathway; 

// Represents a room in the game
class Room {
public:
    Room(const string& name, const string& description);

    // Add an item to the room
    void AddItem(Item* item);

    // Remove an item from the room
    void RemoveItem(Item* item);

    // Find an item in the room by name
    Item* FindItem(const string& itemName);

    // Add a character to the room
    void AddCharacter(Character* character);

    // Remove a character from the room
    void RemoveCharacter(Character* character);

    // Find a character in the room by name
    Character* FindCharacter(const string& characterName);

    // Get the name of the room
    const string& GetName() const;

    // Get the description of the room
    const string& GetDescription() const;

    // Print the room's description
    void PrintDescription() const;

    // Print the items in the room
    void PrintItems() const;

    // Print the characters in the room
    void PrintCharacters() const;

    // Set the room description
    void SetDescription(string);

    // Add a pathway to given room
    void AddPathway(Room* room);

private:
    string name;
    string description;
    std::vector<Item*> items;
    std::vector<Character*> characters;
    std::vector<Pathway*> pathways;
};

#endif  // ROOM_H