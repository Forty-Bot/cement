#include "entity.hpp"
#include "actor.hpp"

#include "libtcod.hpp"

void EntityDisplayC::draw(TCODConsole *con) {
	int x = getParent()->x + getOffsetX();
	int y = getParent()->y + getOffsetY();
	con->setCharForeground(x, y, color);
	con->setChar(x, y, character);
}

Entity::~Entity() {
	if(actor)   delete actor;
	if(display) delete display;
}


