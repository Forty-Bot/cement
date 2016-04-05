#ifndef WORLD_HPP
#define WORLD_HPP

#include "actor.hpp"
#include "entity.hpp"
#include "map.hpp"

#include <set>
#include <vector>

struct EntityCompare {
	bool operator()	(const Entity *a, const Entity *b) const {
		return a->actor->priority < b->actor->priority;
	}
};

class World {
public:
	Entity *player;
	Map *map;
	World(Entity *player, Map *map): player(player), map(map) { add(player); }
	// Get all entities at the given coordinates
	std::vector<Entity *> getEnts(int x, int y);
	void update();
	void add(Entity *e) { ents.insert(e); }
	bool remove(Entity *e);
private:
	std::multiset<Entity *, EntityCompare> ents;
};

#endif // WORLD_HPP
