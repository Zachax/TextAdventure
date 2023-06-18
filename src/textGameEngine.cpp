#include "textGameEngine.h"

TextGameEngine::TextGameEngine() {
    LoadGameData();
    LoadGameState();
}

void TextGameEngine::Run() {
    std::cout << "Welcome to the Adventure Game!" << std::endl;
    std::cout << "Type 'help' for a list of commands." << std::endl;

    while (!gameOver) {
        std::cout << "> ";
        std::string command;
        std::getline(std::cin, command);

        ProcessCommand(command);
    }
}

void TextGameEngine::LoadGameData() {
    // Load room data from a file
    std::ifstream roomFile("data/rooms.txt");
    if (!roomFile) {
        std::cerr << "Error: Failed to open room data file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(roomFile, line)) {
        // Process room data from the file and create Room objects
        if (!line.empty()) {
            std::string roomName = line;
            std::getline(roomFile, line);
            std::string roomDescription = line;

            Room* room = new Room(roomName, roomDescription);
            rooms.push_back(room);
        }
    }

    roomFile.close();

    // Load item data from a file
    std::ifstream itemFile("data/items.txt");
    if (!itemFile) {
        std::cerr << "Error: Failed to open item data file." << std::endl;
        return;
    }

    while (std::getline(itemFile, line)) {
        // Process item data from the file and create Item objects
        if (!line.empty()) {
            std::string itemName = line;

            std::getline(itemFile, line);
            std::string itemDescription = line;

            std::getline(itemFile, line);
            bool itemMovable = (line == "movable");

            Item* item = new Item(itemName, itemDescription, itemMovable);
            items.push_back(item);
        }
    }

    itemFile.close();

    // Load character data from a file
    std::ifstream characterFile("data/characters.txt");
    if (!characterFile) {
        std::cerr << "Error: Failed to open character data file." << std::endl;
        return;
    }

    while (std::getline(characterFile, line)) {
        // Process character data from the file and create Character objects
        if (!line.empty()) {
            std::string characterName = line;

            std::getline(characterFile, line);
            std::string characterDescription = line;

            std::getline(characterFile, line);
            bool characterPlayerControlled = (line == "player");

            Character* character = new Character(characterName, characterDescription, characterPlayerControlled);
            characters.push_back(character);
        }
    }

    characterFile.close();

    // Set the initial current room
    currentRoom = rooms[0];
}

void TextGameEngine::LoadRoomData(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << fileName << std::endl;
        return;
    }

    std::string line;
    std::string currentSection;
    Room* currentRoom = nullptr;

    while (std::getline(file, line)) {
        // Remove leading and trailing whitespaces from the line
        line = Trim(line);

        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // Check if the line denotes a new section
        if (line[0] == '[' && line[line.length() - 1] == ']') {
            // Extract the section name from the line
            currentSection = line.substr(1, line.length() - 2);
            continue;
        }

        // Parse the line based on the current section
        if (currentSection == "Room") {
            // Parse room data
            if (line == "Name=") {
                // Extract the room name from the line
                std::string roomName = line.substr(5);
                currentRoom = new Room(roomName, "");
                rooms.push_back(currentRoom);
            } else if (line == "Description=") {
                // Extract the room description from the line
                std::string roomDescription = line.substr(12);
                currentRoom->SetDescription(roomDescription);
            }
        } else if (currentSection == "Pathways") {
            // Parse pathways data
            size_t arrowPos = line.find("->");
            if (arrowPos != std::string::npos) {
                std::string sourceRoomName = line.substr(0, arrowPos);
                std::string destinationRoomName = line.substr(arrowPos + 2);
                Room* sourceRoom = FindRoomByName(sourceRoomName);
                Room* destinationRoom = FindRoomByName(destinationRoomName);
                if (sourceRoom && destinationRoom) {
                    sourceRoom->AddPathway(destinationRoom);
                }
            }
        } else if (currentSection == "Items") {
            // Parse items data
            size_t arrowPos = line.find("->");
            if (arrowPos != std::string::npos) {
                std::string roomName = line.substr(0, arrowPos);
                std::string itemName = line.substr(arrowPos + 2);
                Room* room = FindRoomByName(roomName);
                Item* item = FindItemByName(itemName);
                if (room && item) {
                    room->AddItem(item);
                }
            }
        } else if (currentSection == "Characters") {
            // Parse characters data
            size_t arrowPos = line.find("->");
            if (arrowPos != std::string::npos) {
                std::string roomName = line.substr(0, arrowPos);
                std::string characterName = line.substr(arrowPos + 2);
                Room* room = FindRoomByName(roomName);
                Character* character = FindCharacterByName(characterName);
                if (room && character) {
                    room->AddCharacter(character);
                }
            }
        }
    }

    file.close();
}

void TextGameEngine::SaveGameState() {
    std::ofstream gameStateFile("gamestate.sav");
    if (!gameStateFile) {
        std::cerr << "Error: Failed to create game state file." << std::endl;
        return;
    }

    // Save the current room
    gameStateFile << currentRoom->GetName() << std::endl;

    // Save other game state information as needed

    gameStateFile.close();

    std::cout << "Game state saved." << std::endl;
}

void TextGameEngine::LoadGameState() {
    std::ifstream gameStateFile("gamestate.sav");
    if (!gameStateFile) {
        std::cout << "No saved game state found." << std::endl;
        return;
    }

    std::string roomName;
    if (std::getline(gameStateFile, roomName)) {
        // Find the corresponding room object by name
        for (auto& room : rooms) {
            if (room->GetName() == roomName) {
                currentRoom = room;
                break;
            }
        }
    }

    // Load other game state information as needed

    gameStateFile.close();

    std::cout << "Game state loaded." << std::endl;
}

Room* TextGameEngine::FindRoomByName(const std::string& roomName) {
    for (Room* room : rooms) {
        if (room->GetName() == roomName) {
            return room;
        }
    }
    return nullptr;
}

Item* TextGameEngine::FindItemByName(const std::string& itemName) {
    for (Item* item : items) {
        if (item->GetName() == itemName) {
            return item;
        }
    }
    return nullptr;
}

Character* TextGameEngine::FindCharacterByName(const std::string& characterName) {
    for (Character* character : characters) {
        if (character->GetName() == characterName) {
            return character;
        }
    }
    return nullptr;
}

std::string TextGameEngine::Trim(const std::string& str) {
    const std::string whitespace = " \t";
    const auto start = str.find_first_not_of(whitespace);
    const auto end = str.find_last_not_of(whitespace);
    return str.substr(start, end - start + 1);
}

void TextGameEngine::ProcessCommand(const std::string& command) {
    if (command.empty()) {
        return;
    }

    // Split the command into tokens
    std::istringstream iss(command);
    std::vector<std::string> tokens(std::istream_iterator<std::string>{iss},
                                    std::istream_iterator<std::string>());

    if (tokens.empty()) {
        return;
    }

    // Extract the command verb (first token)
    std::string verb = tokens[0];

    // Check for abbreviated commands
    if (verb.size() == 1) {
        // Abbreviate take command
        if (verb == "t") {
            verb = "take";
        }
        // Abbreviate look command
        else if (verb == "l") {
            verb = "look";
        }
        // Abbreviate use command
        else if (verb == "u") {
            verb = "use";
        }
        // Abbreviate inventory command
        else if (verb == "i") {
            verb = "inventory";
        }
        // Abbreviate help command
        else if (verb == "h") {
            verb = "help";
        }
    }

    // Process the command
    if (verb == "take") {
        // Handle take command
        // Implement
    }
    else if (verb == "look") {
        // Handle look command
        if (tokens.size() == 1) {
            currentRoom->PrintDescription();
            currentRoom->PrintItems();
            currentRoom->PrintCharacters();
        }
        else {
            // Handle looking at specific item or character
            // Implement
        }
    }
    else if (verb == "use") {
        // Handle use command
        // Implement
    }
    else if (verb == "inventory") {
        // Handle inventory command
        // Implement
    }
    else if (verb == "quit") {
        // Handle quit command
        std::cout << "Thanks for playing!\nQuitting game..." << std::endl;
        exit(0);
    }
    else if (verb == "help") {
        // Handle help command
        std::cout << "Available commands:" << std::endl;
        std::cout << "help - This information" << std::endl;
        std::cout << "take <item> - Take an item" << std::endl;
        std::cout << "look - Look around the room" << std::endl;
        std::cout << "use <item> - Use an item" << std::endl;
        std::cout << "inventory - View your inventory" << std::endl;
        std::cout << "quit - Quit game" << std::endl;
        // Add additional commands here
    }
    else {
        std::cout << "Invalid command. Type 'help' for a list of commands." << std::endl;
    }
}