#include <string>
#include "Item.h"
#include "ItemTextbook.h"

//make a new textbook
ItemTextbook::ItemTextbook(std::string name, int maxuses) : Item(name, maxuses) {
	_name = "Textbook on: " + name;
}

ItemTextbook::~ItemTextbook() {
}

/**
Use a textbook which adds 10 * the number used as defense to the Player
Applied via Player function
*/
int ItemTextbook::use(int consumed) {
	return Item::use(consumed) * 10;

}
