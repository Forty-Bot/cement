#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <libtcod/libtcod.hpp>

class Entity;
class ActorC;

class Component {
public:
	virtual ~Component() {}
	virtual void update(int delta) = 0;
	Entity *getParent() {return parent;}
protected:
	Component(Entity *parent): parent(parent) {}
private:
	Entity *parent;
};

/*
 * The display component draws an entity onto the screen (or doesn't) depending on the properties of the
 * entity.
 */
class DisplayC: public Component {
public:
	DisplayC(Entity *parent, int character, TCODColor color): Component(parent), character(character),
		color(color) {}
	void setCharacter(int character) {this->character = character;}
	void setColor(TCODColor color) {this->color = color;}
	void draw(TCODConsole *con, int offset_x, int offset_y);
	virtual void update(int delta) {};
private:
	int character;
	TCODColor color;
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
	DisplayC *display;
	//CombatC *combat;
	~Entity();
};

#endif // ENTITY_HPP
