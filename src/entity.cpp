#include "entity.hpp"
#include "actor.hpp"

#include "libtcod.hpp"

void DisplayC::draw(TCODConsole *con, int offset_x, int offset_y) {
	int x = getParent()->x + offset_x;
	int y = getParent()->y + offset_y;
	con->setCharForeground(x, y, this->color);
	con->setChar(x, y, this->character);
}

Entity::~Entity() {
	if(actor)   delete actor;
	if(display) delete display;
}


