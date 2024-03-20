#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Room {
    string description;
    map<string, int> exits;
    set<string> items;
};

struct Item {
    string name;
    string description;
};

int main() {
    cout << "Welcome to the Murder on the Orient Express Adventure Game!" << endl;

    // Define items
    map<string, Item> items = {
        {"note", {"note", "A cryptic note that might hold a clue to the murder."}},
        {"key", {"key", "A small key found in the victim's compartment."}},
        {"watch", {"watch", "A gold watch that seems out of place."}},
        {"diary", {"diary", "A diary belonging to another passenger. It contains some interesting entries."}}
    };

    // Define the game world
    vector<Room> rooms = {
        {"You are in your compartment on the Orient Express. The train has stopped due to snow. There is a door to the east.", {{"east", 1}}, {}},
        {"You are in the corridor. There is a suspicious-looking passenger here. Doors lead west and east.", {{"west", 0}, {"east", 2}}, {"note"}},
        {"You are in the dining car. The atmosphere is tense. There is a door to the west and another to the east.", {{"west", 1}, {"east", 3}}, {"key"}},
        {"You are in the victim's compartment. There is a locked drawer here. There is a door to the west.", {{"west", 2}}, {}},
        {"You are in the library. There are many books and a comfortable chair. There is a door to the west.", {{"west", 2}}, {"diary"}},
        {"You are in a secret compartment. It's dark and cramped. There is a door to the south.", {{"south", 2}}, {"watch"}}
    };

    int currentRoom = 0;
    set<string> inventory;
    bool murderSolved = false;

    // Easter egg
    bool easterEggFound = false;

    // Game loop
    while (!murderSolved) {
        cout << rooms[currentRoom].description << endl;

        // List items in the room
        if (!rooms[currentRoom].items.empty()) {
            cout << "You see the following items: ";
            for (const auto& item : rooms[currentRoom].items) {
                cout << item << " ";
            }
            cout << endl;
        }

        // Get player command
        string command;
        cout << "> ";
        getline(cin, command);

        // Process commands
        if (command == "quit") {
            cout << "Thank you for playing!" << endl;
            break;
        } else if (command == "solve murder") {
            if (inventory.count("note") && inventory.count("key")) {
                cout << "Using the note and the key, you deduce that the suspicious-looking passenger is the murderer. You have solved the murder!" << endl;
                murderSolved = true;
            } else {
                cout << "You don't have enough evidence to solve the murder yet." << endl;
            }
        } else if (command == "read diary" && inventory.count("diary")) {
            cout << "The diary contains entries about a mysterious figure seen lurking around the train. It seems like a red herring." << endl;
        } else if (command == "examine watch" && inventory.count("watch")) {
            if (!easterEggFound) {
                cout << "The watch has an engraving: 'Time is the key.' This might be a clue or just an Easter egg." << endl;
                easterEggFound = true;
            } else {
                cout << "It's just a watch with a cryptic engraving." << endl;
            }
        } else if (command.substr(0, 4) == "take") {
            string itemName = command.substr(5);
            if (rooms[currentRoom].items.count(itemName)) {
                inventory.insert(itemName);
                rooms[currentRoom].items.erase(itemName);
                cout << "You take the " << itemName << "." << endl;
            } else {
                cout << "There is no " << itemName << " here." << endl;
            }
        } else if (command.substr(0, 4) == "drop") {
            string itemName = command.substr(5);
            if (inventory.count(itemName)) {
                inventory.erase(itemName);
                rooms[currentRoom].items.insert(itemName);
                cout << "You drop the " << itemName << "." << endl;
            } else {
                cout << "You don't have a " << itemName << "." << endl;
            }
        } else if (command == "inventory") {
            if (!inventory.empty()) {
                cout << "You are carrying: ";
                for (const auto& item : inventory) {
                    cout << item << " ";
                }
                cout << endl;
            } else {
                cout << "Your inventory is empty." << endl;
            }
        } else if (rooms[currentRoom].exits.find(command) != rooms[currentRoom].exits.end()) {
            currentRoom = rooms[currentRoom].exits[command];
        } else {
            cout << "You can't go that way." << endl;
        }
    }

    return 0;
}
