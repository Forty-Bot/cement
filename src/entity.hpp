#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "libtcod.hpp"

class Entity;
class ActorC;

class Component {
public:
	virtual ~Component() {}
	Entity *getParent() {return parent;}
protected:
	Component(Entity *parent): parent(parent) {}
private:
	Entity *parent;
};

/*
 * The display component draws something onto the screen (or doesn't) depending on the properties of the
 * entity.
 */
class DisplayC {
public:
	void setOffset(int x, int y) {offset_x = x; offset_y = y;}
	int getOffsetX() {return offset_x;}
	int getOffsetY() {return offset_y;}
	virtual void draw(TCODConsole *con) = 0;
	virtual ~DisplayC() {}
protected:
	DisplayC(): offset_x(0), offset_y(0) {} 
private:
	int offset_x;
	int offset_y;
};

/*
 * Display component of an Entity.
 */
class EntityDisplayC: public DisplayC, public Component {
public:
	EntityDisplayC(Entity *parent, int character, TCODColor color): DisplayC(), Component(parent),
		color(color), character(character) {}
	void setColor(TCODColor color) {this->color = color;}
	void setCharacter(int character) {this->character = character;}
	virtual void draw(TCODConsole *con);
private:
	TCODColor color;
	int character;
};

/*
 * An entity is something in the world. It can be inanimate or a creature, have stats or not, or hold other
 * entities. Each of these optionals is abstracted away by a component. In fact, entitties are mainly just
 * containers for other behaviors.
 */
class Entity{
public:
	int x;
	int y;
	ActorC *actor;
	EntityDisplayC *display;
	//CombatC *combat;
	~Entity();
};

#endif // ENTITY_HPP
