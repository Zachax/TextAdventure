#ifndef ITEM_H
#define ITEM_H

#include <string>

// Represents an item in the game
class Item {
public:
    Item(const std::string& name, const std::string& description, bool movable = true);

    const std::string& GetName() const;
    const std::string& GetDescription() const;
    bool IsMovable() const;

private:
    std::string name;
    std::string description;
    bool movable;
};

#endif  // ITEM_H