#ifndef WORLD_HPP
#define WORLD_HPP

#include "actor.hpp"
#include "entity.hpp"

#include <set>

struct EntityCompare {
	bool operator()	(const Entity *a, const Entity *b) const {
		return a->actor->priority < b->actor->priority;
	}
};

class World {
public:
	void update();
	void add(Entity *e) { ents.insert(e); }
	bool remove(Entity *e);
private:
	std::multiset<Entity *, EntityCompare> ents;
};

#endif // WORLD_HPP
