#ifndef WORLD_HPP
#define WORLD_HPP

#include "actor.hpp"
#include "entity.hpp"

#include <queue>
#include <vector>

/*
 * A tile is a bit of floor in a map
 */
class Tile {
public:
	bool walkable;
	TCODColor color;
	static Tile const Wall;
	static Tile const Floor;
	virtual void draw(TCODConsole *con, int x, int y) {con->setCharBackground(x, y, color);}
private:
	Tile(bool walkable, TCODColor color): walkable(walkable), color(color) {}
};

struct ActorCompare {
	bool operator()	(const ActorC *a, const ActorC *b) const {
		return a->priority > b->priority;
	}
};

class World {
public:
	void add(Entity *e) { push(e->actor); }
	// TODO: void remove(ActorC *e);
	void update();
private:
	void push(ActorC *a);
	ActorC *peek() { return actors.front(); }
	ActorC *pop();
	std::vector<ActorC *> actors;
};

#endif // WORLD_HPP
