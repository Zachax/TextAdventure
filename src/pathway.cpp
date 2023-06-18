#include "pathway.h"

Pathway::Pathway(Room* source, Room* destination)
    : sourceRoom(source), destinationRoom(destination) {
}

Room* Pathway::GetSourceRoom() const {
    return sourceRoom;
}

Room* Pathway::GetDestinationRoom() const {
    return destinationRoom;
}
