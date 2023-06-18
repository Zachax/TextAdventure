#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

// Represents a character in the game
class Character {
public:
    Character(const std::string& name, const std::string& description, bool playerControlled = false);

    const std::string& GetName() const;
    const std::string& GetDescription() const;
    bool IsPlayerControlled() const;

private:
    std::string name;
    std::string description;
    bool playerControlled;
};

#endif  // CHARACTER_H