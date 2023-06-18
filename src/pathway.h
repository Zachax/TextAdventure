#ifndef PATHWAY_H
#define PATHWAY_H

#include "room.h"

class Room;

class Pathway {
public:
    Pathway(Room* source, Room* destination);

    Room* GetSourceRoom() const;
    Room* GetDestinationRoom() const;

private:
    Room* sourceRoom;
    Room* destinationRoom;
};

#endif // PATHWAY_H