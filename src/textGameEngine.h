#ifndef TEXT_GAME_ENGINE_H
#define TEXT_GAME_ENGINE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

#include "room.h"
#include "item.h"
#include "character.h"

using string = std::string;

// Forward declarations
class Room;
class Item;
class Character;

// Represents the game engine
class TextGameEngine {
public:
    TextGameEngine();

    void Run();

private:
    void LoadGameData();
    void LoadRoomData(const string& fileName);
    void SaveGameState(); 
    void LoadGameState();
    Room* FindRoomByName(const string& roomName);
    Item* FindItemByName(const string& itemName);
    Character* FindCharacterByName(const string& characterName);
    string Trim(const string& str);
    void ProcessCommand(const string& command);

    bool gameOver = false;

    std::vector<Room*> rooms;
    std::vector<Item*> items;
    std::vector<Character*> characters;
    Room* currentRoom = nullptr;
};

#endif  // TEXT_GAME_ENGINE_H