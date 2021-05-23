/**
*projectName FinalProject
*author  Zeyuan Song
*studentID 19096216
*Date 12/05/2020
*/
#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "item.h"
using namespace std;
using std::vector;

class Room {
    /*****friend*****/
    friend class mainwindow;
private:
	string description;
	map<string, Room*> exits;

    vector <Item> itemsInRoom;

public:
    string exitString();
    string roomItems();
    int numberOfItems();
	Room(string description);
	void setExits(Room *north, Room *east, Room *south, Room *west);
	string shortDescription();
	string longDescription();
	Room* nextRoom(string direction);
    void addItem(Item *inItem);
    void deleteItem(int m);
    string displayItem();
    int isItemInRoom(string inString);
    void removeItemFromRoom(int location);
    int checkItems(string m);

};

#endif
